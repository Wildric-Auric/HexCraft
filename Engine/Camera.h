//TODO::Use my 
#include "glm/glm.hpp"
#include "Globals.h"


#define DEFAULT_RESOLUTION_X 720.0f
#define DEFAULT_RESOLUTION_Y 480.0f
#define DEFAULT_NEAR_PLANE   DEFAULT_RESOLUTION_Y * 0.5f
#define DEFAULT_FAR_PLANE    16777215.0f //2^24 - 1  = 4438 meter
#define DEFAULT_ORTHO_PLANE  DEFAULT_RESOLUTION_Y * 0.5f

constexpr float defaultAspectRatio     = DEFAULT_RESOLUTION_X / DEFAULT_RESOLUTION_Y;
//If fieldOfView is 0.0f it will be set automatically according to orthoPlane
//Distance at which the frustum plane matches a pixel perfect orthographic projection
struct CameraProperties {
	fVec2 resolution          = fVec2(DEFAULT_RESOLUTION_X, DEFAULT_RESOLUTION_Y);
	float nearPlane           = DEFAULT_NEAR_PLANE;
	float farPlane            = DEFAULT_FAR_PLANE;
	float orthoPlane          = DEFAULT_ORTHO_PLANE;
	float fieldOfView		  =	0.0f;
	float aspectRatio		  = defaultAspectRatio;
};

class Camera {
public:

	glm::mat4 __viewMatrix             = glm::mat4(1.0);
	glm::mat4 __projectionMatrix       = glm::mat4(1.0);
	fVec3	  __position               = fVec3(0.0f, 0.0f, 1.0f);
	CameraProperties  __prop;

	//Stores the result of projection matrix multiplied by view matrix, should be updated with the update of the latters
	glm::mat4 VP;

	static Camera* activeCam;

	Camera() {};
	Camera(const fVec2& resolution, const fVec3& position = fVec3(0.0f, 0.0f, 1.0f));
	Camera(const CameraProperties&  camProp);
	void CalculateViewMatrix();
	void CalculateViewXprojection();
	void CalculateProjectionMatrix(const CameraProperties& camProp);
	void MoveTo(const fVec3& newPos);
	void Use();
};	