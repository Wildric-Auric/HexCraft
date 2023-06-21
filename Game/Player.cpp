#include "Player.h"
#include "Camera.h"
#include "Inputs.h"
#include "FPS.h"
#include "CoordinateSystem.h"
#include "UnitHex.h"
#include "Noise.h"
#include "Demo.h"
#include <iostream>
#include <ostream>

using std::size;
static UnitHex tt;

//Rappel : Normaliser le déplacement <=> *FPS::deltaTime

void Player::Start() {
	//Inputs::keyBoardMode = KeyBoardMode::INPUT_AZERTY;
}

bool Player::Collision(fVec3 futurPosition) {
	return Demo::BlockPresent(futurPosition);
}

void Player::Update() { //int height
	float yBlock = tt.size.y;
	//Gestion vitesse déplacement 
	if (Inputs::KeyPressed(HEX_INPUT_KEY_RIGHT_CONTROL)) {
		if (this->speed == this->speedNormal)
			this->speed = this->speedHight;
		else
			this->speed = this->speedNormal;
	}
	else if (Inputs::KeyPressed(HEX_INPUT_KEY_RIGHT_SHIFT)) {
		if (this->speed == this->speedNormal)
			this->speed = this->speedLow;
		else
			this->speed = this->speedNormal;
	}

	float xDir = Inputs::DirectionalKeyPressed(DirectionalKey::INPUT_RIGHT) - Inputs::DirectionalKeyPressed(DirectionalKey::INPUT_LEFT);
	float yDir = Inputs::DirectionalKeyPressed(DirectionalKey::INPUT_UP) - Inputs::DirectionalKeyPressed(DirectionalKey::INPUT_DOWN);
	fVec2 movDir = fVec2(xDir, yDir).normalize();//caméra 

	float xDir0 = Inputs::KeyPressed(HEX_INPUT_KEY_LEFT) - Inputs::KeyPressed(HEX_INPUT_KEY_RIGHT);
	float yDir0 = Inputs::KeyPressed(HEX_INPUT_KEY_UP) - Inputs::KeyPressed(HEX_INPUT_KEY_DOWN);

	int espaceDir = Inputs::KeyPressed(HEX_INPUT_KEY_SPACE); //Barre Espace
	int leftShiftDir = Inputs::KeyPressed(HEX_INPUT_KEY_LEFT_SHIFT);

	this->forward = Maths::SphericalToCartesian(Camera::activeCam->__rotation).normalize();

	//std::cout << forward.x << ", " << forward.y << ", " << forward.z << " ; " << std::endl;

	forward.y = 0;
	fVec3 right = forward.Cross(fVec3(0.0, 1.0, 0.0));
	fVec3 result = ((right * movDir.x * speed.x + forward * movDir.y * speed.y) * FPS::deltaTime * (Inputs::KeyPressed(HEX_INPUT_KEY_LEFT_CONTROL) ? acceleration : 1.0));

	fVec3 futurPos = this->position + result;

	if (this->Mode == 0) { //Vole
		fVec3 regard = Maths::SphericalToCartesian(Camera::activeCam->__rotation).normalize();

		if (!Collision(futurPos)) {
			int deplacement = 0;
			if (espaceDir == 1) {
				deplacement = 2.0 * yBlock * FPS::deltaTime;
			}
			else if (leftShiftDir == 1) {
				deplacement = -2.0 * yBlock * FPS::deltaTime;
			}
			futurPos.y = futurPos.y + deplacement;
		}
	}

	else if (this->Mode == 1) { //Marche
		//si pas bloc sous lui alors tombé chute libre
		//bool isGrounded = this->position.y <= 0; //voir QUAND ON EST sur la map
		bool isGrounded = this->position.y <= CoordinateSystem::HeightInWorld(this->position) * yBlock;
		//std::cout << this->position.y << " ; " << CoordinateSystem::HeightInWorld(this->position) << std::endl;
		bool estDansleVide = this->position.y <= 0;
		speedAltitude = Maths::Max(speedAltitude - yBlock, yBlock * minAltitude);
		if (isGrounded) {
			speedAltitude = 0.0f;
		}
		if (estDansleVide) {
			speedAltitude = -yBlock;
		}
		// ici mettre dans if || ( sautAuto && collision) pour saut auto 
		if ((espaceDir && isGrounded) && !estDansleVide) {  //|| (SautAuto && Collision(futurPos))
			speedAltitude = yBlock * maxAltitude;
		}

		futurPos.y += speedAltitude * FPS::deltaTime;
		//std::cout << speedAltitude;
	}
	//std::cout << futurPos.x << ", " << futurPos.y << ", " << futurPos.z << " ; " << std::endl;
	//std::cout << Collision(futurPos) << " ; " << Demo::BlockPresent(futurPos)  <<  std::endl;
	if (!Collision(futurPos)) {

		this->position = futurPos;
	}

	this->rotation = this->rotation + fVec2(xDir0, yDir0).normalize() * sensitivty * FPS::deltaTime * (Inputs::KeyPressed(HEX_INPUT_KEY_LEFT_CONTROL) ? acceleration : 1.0);
	this->rotation.y = Maths::Clamp<float>(this->rotation.y, -89.8, 89.8);

	Camera::activeCam->UpdateTranform(this->position, this->rotation);

}

