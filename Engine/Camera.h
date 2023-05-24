//TODO::Use matrices in Maths.h instead of glm

#include "glm/glm.hpp"
#include "Globals.h"


#define DEFAULT_RESOLUTION_X 1720.0f
#define DEFAULT_RESOLUTION_Y 1080.0f
#define DEFAULT_NEAR_PLANE   DEFAULT_RESOLUTION_Y * 0.001f
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
	//rotation.x is angle between XZ and rotation.y between XY, stored in radian
	fVec2     __rotation               = fVec2(0.0f, 0.0f);
	CameraProperties  __prop;

	//Stores the result of projection matrix multiplied by view matrix, should be updated with the update of the latters
	glm::mat4 VP = glm::mat4(1.0);

	static Camera* activeCam;

	Camera() {};
	Camera(const fVec2& resolution, const fVec3& position = fVec3(0.0f, 0.0f, 1.0f), const fVec2& rotation = fVec2(0.0f, 0.0f));
	Camera(const CameraProperties&  camProp, const fVec3& position = fVec3(0.0f, 0.0f, 1.0f), const fVec2& rotation = fVec2(0.0f, 0.0f));
	void CalculateViewMatrix();
	void CalculateViewXprojection();
	void CalculateProjectionMatrix(const CameraProperties& camProp);
	void UpdateTranform(const fVec3& newPos, const fVec2& newRot = fVec2());
	void Use();
};