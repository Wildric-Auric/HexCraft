//TODO::Stop using glm and use only maths.h

#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"


Camera* Camera::activeCam		= nullptr;

void Camera::CalculateViewMatrix() {
	glm::vec3 pos			 = glm::vec3(this->__position.x, this->__position.y, this->__position.z);
	//Conversion from spherical coordinates to cartesian coordinates
	fVec3 temp                     = Maths::SphericalToCartesian(this->__rotation);
	glm::vec3 dir			       = glm::vec3(temp.x, temp.y, temp.z);
	this->__viewMatrix		       = glm::lookAt(pos, pos + dir, glm::vec3(0.0, 1.0, 0.0));
	this->CalculateViewXprojection();
}

void Camera::CalculateProjectionMatrix(const CameraProperties& camProp) {
	this->__prop			 = camProp;
	if (this->__prop.fieldOfView == 0.0f) {
		this->__prop.fieldOfView = 2.0 * Maths::RadToDeg(atan(this->__prop.resolution.y * 0.5 / this->__prop.orthoPlane));
	}
	this->__prop.aspectRatio = this->__prop.resolution.x / this->__prop.resolution.y;
	this->__projectionMatrix = glm::perspective(Maths::DegToRad(this->__prop.fieldOfView), this->__prop.aspectRatio, this->__prop.nearPlane, this->__prop.farPlane);
	this->CalculateViewXprojection();
}

void Camera::CalculateViewXprojection() {
	this->VP = this->__projectionMatrix * this->__viewMatrix;
}

void Camera::UpdateTranform(const fVec3& newPos, const fVec2& newRot) {
	if (this->__position == newPos && this->__rotation == newRot)
		return;
	this->__position = newPos;
	this->__rotation = fVec2(Maths::DegToRad(newRot.x), Maths::DegToRad(newRot.y));
	this->CalculateViewMatrix();
}

//Angles of rotation are passed in degree
Camera::Camera(const fVec2& resolution, const fVec3& position, const fVec2& rotation) {
	CameraProperties prop;
	prop.resolution = resolution;
	this->CalculateProjectionMatrix(prop);
	this->UpdateTranform(position, rotation);
}
//Angles of rotation are passed in degree
Camera::Camera(const CameraProperties& camProp, const fVec3& position, const fVec2& rotation) {
	this->CalculateProjectionMatrix(camProp);
	this->UpdateTranform(position, rotation);
}

void Camera::Use() {
	Camera::activeCam = this;
}