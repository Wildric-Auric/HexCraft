//TODO::Stop using glm and use only maths.h

#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"


Camera* Camera::activeCam		= nullptr;

void Camera::CalculateViewMatrix() {
	this->__viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-this->__position.x, -this->__position.y, -this->__position.z));
	this->CalculateViewXprojection();
}

void Camera::CalculateProjectionMatrix(const CameraProperties& camProp) {
	this->__prop			 = camProp;
	this->__prop.aspectRatio = this->__prop.resolution.x / this->__prop.resolution.y;
	this->__projectionMatrix = glm::perspective(Maths::DegToRad(this->__prop.fieldOfView), this->__prop.aspectRatio, this->__prop.nearPlane, this->__prop.farPlane);
	this->CalculateViewXprojection();
}

void Camera::CalculateViewXprojection() {
	this->VP = this->__projectionMatrix * this->__viewMatrix;
}

void Camera::MoveTo(const fVec3& newPos) {
	this->__position = newPos;
	this->CalculateViewMatrix();
}

Camera::Camera(const fVec2& resolution, const fVec3& position) {
	CameraProperties prop;
	prop.resolution = resolution;
	this->CalculateProjectionMatrix(prop);
	this->MoveTo(position);
}

Camera::Camera(const CameraProperties& camProp) {
	this->CalculateProjectionMatrix(camProp);
	this->CalculateViewMatrix();
}

void Camera::Use() {
	Camera::activeCam = this;

}