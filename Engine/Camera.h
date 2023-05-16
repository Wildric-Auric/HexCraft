//TODO::Use my 
#include "glm/glm.hpp"
#include "Globals.h"


#define DEFAULT_RESOLUTION_X 720.0f
#define DEFAULT_RESOLUTION_Y 480.0f
#define DEFAULT_NEAR_PLANE   1.0f
#define DEFAULT_FAR_PLANE    1000.0f

constexpr float defaultAspectRatio     = DEFAULT_RESOLUTION_X / DEFAULT_RESOLUTION_Y;
//Read only
struct CameraProperties {
	fVec2 resolution          = fVec2(DEFAULT_RESOLUTION_X, DEFAULT_RESOLUTION_Y);
	float fieldOfView		  = 60.0f;
	float nearPlane           = 1.0f;
	float farPlane            = 1000.0f;
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