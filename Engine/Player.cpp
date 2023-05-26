#include "Player.h"
#include "Camera.h"
#include "Inputs.h"
void Player::Start() {
	Inputs::keyBoardMode = KeyBoardMode::INPUT_AZERTY;
}


//void Player::Update() {
//	float xDir = Inputs::DirectionalKeyPressed(DirectionalKey::INPUT_RIGHT) - Inputs::DirectionalKeyPressed(DirectionalKey::INPUT_LEFT);
//	float yDir = Inputs::DirectionalKeyPressed(DirectionalKey::INPUT_UP) - Inputs::DirectionalKeyPressed(DirectionalKey::INPUT_DOWN);
//
//	
//	float xDir0 = Inputs::KeyPressed(HEX_INPUT_KEY_RIGHT) - Inputs::KeyPressed(HEX_INPUT_KEY_LEFT);
//	float yDir0 = Inputs::KeyPressed(HEX_INPUT_KEY_UP)    - Inputs::KeyPressed(HEX_INPUT_KEY_DOWN);
//
//	fVec3 speed0 = 
//	this->position   = this->position        + fVec3(xDir, yDir).normalize() * speed0 * (Inputs::KeyPressed(HEX_INPUT_KEY_LEFT_SHIFT) ? acceleration : 1.0);
//	this->rotation   = this->rotation + fVec2(xDir0, yDir0).normalize() * speed * (Inputs::KeyPressed(HEX_INPUT_KEY_LEFT_SHIFT) ? acceleration : 1.0);
//	this->rotation.x = Maths::Clamp<float>(this->rotation.x, -89.8, 89.8);
//	this->rotation.y = Maths::Clamp<float>(this->rotation.y, -89.8, 89.8);
//	
//	Camera::activeCam->UpdateTranform(this->position, this->rotation);
//}
//
//
