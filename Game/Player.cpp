#include "Player.h"
#include "Camera.h"
#include "Inputs.h"
#include "FPS.h"
#include "CoordinateSystem.h"

#include "UnitHex.h"
#include <deque>

extern std::deque<UnitHex> worldMap;

void Player::Start() {
	//Inputs::keyBoardMode = KeyBoardMode::INPUT_AZERTY;
}


void Player::Update() {
	float xDir = Inputs::DirectionalKeyPressed(DirectionalKey::INPUT_RIGHT) - Inputs::DirectionalKeyPressed(DirectionalKey::INPUT_LEFT);
	float yDir = Inputs::DirectionalKeyPressed(DirectionalKey::INPUT_UP) - Inputs::DirectionalKeyPressed(DirectionalKey::INPUT_DOWN);
	fVec2 movDir = fVec2(xDir, yDir).normalize();
	
	float xDir0   = Inputs::KeyPressed(HEX_INPUT_KEY_LEFT) - Inputs::KeyPressed(HEX_INPUT_KEY_RIGHT);
	float yDir0   = Inputs::KeyPressed(HEX_INPUT_KEY_UP)    - Inputs::KeyPressed(HEX_INPUT_KEY_DOWN);
	
	this->forward = Maths::SphericalToCartesian(Camera::activeCam->__rotation);
	fVec3 right   = forward.Cross(fVec3(0.0, 1.0, 0.0)).normalize();

	//fVec3 result     =  (right * movDir.x * speed.x + forward * movDir.y * speed.y) * FPS::deltaTime *(Inputs::KeyPressed(HEX_INPUT_KEY_LEFT_SHIFT) ? acceleration : 1.0);
	fVec3  result = fVec3(0.0);
	result.z = -FPS::deltaTime * 5000.0;

    fVec3 nextPos   = this->position  +  result;
	nextPos.y       = 60 * 500.0f;

	this->position  = nextPos;
	this->rotation   = this->rotation  + fVec2(xDir0, yDir0).normalize() * sensitivty * FPS::deltaTime *
					 (Inputs::KeyPressed(HEX_INPUT_KEY_LEFT_SHIFT) ? acceleration : 1.0);

	this->rotation.y = Maths::Clamp<float>(this->rotation.y, -89.8, 89.8);
	this->rotation.x = Maths::Clamp<float>(this->rotation.x, -89.8, 89.8);
	
	Camera::activeCam->UpdateTranform(this->position, this->rotation);
}


