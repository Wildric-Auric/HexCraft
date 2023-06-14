#pragma once
#include "Inventaire.h"
#include "Globals.h"

class Player {
public:

	fVec3 position;
	fVec2 rotation;
	float tailleHauteur = 1.75; // c la taille irl de Reis 1.75 // 1.65 Keren // 1.53 Davina

	fVec2 speedHight = fVec2(3000.0, 5000.0f);
	fVec2 speedNormal = fVec2(750.0, 1250.0f);
	fVec2 speedLow = fVec2(750.0, 1250.0f);
	fVec2 speed = speedNormal; //par défaut

	float speedAltitude = 0.0f; //par défaut
	float minAltitude = -10.0f; // à -10 blocks sur niveau 0
	float maxAltitude = 20.0f; // à 20 blocks au dessus du niv 0

	fVec2 sensitivty = fVec2(30.0, 30.0);
	float acceleration = 3.0;
	//float rotAcc       = 3.0;

	int Mode = 0; //=0 vole ; =1 marche //im gui
	int SautAuto = 1; //1 oui sinon 0 non //imgui

	Inventaire Inv;
	void Start();
	int Collision(fVec3 futurPosition);
	void Update();

};