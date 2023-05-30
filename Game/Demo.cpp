#include "Demo.h"
#include "UnitHex.h"
#include "Camera.h"
#include "Texture.h"
#include "Player.h"
#include "CoordinateSystem.h"
#include <iostream>

#include "imgui/imgui.h"

#include <deque>

static 	Shader shader;
static Texture tex;
static float specularStrength = 0.0f;
static float specularPower    = 256.0f;
static Player player;
static iVec3 mapSize          = iVec3(10, 10, 10);
static fVec3 lightPosition;
static Camera cam;

//using std::size;

std::deque<UnitHex> worldMap;

Demo::Demo() {
	//Loads shader
	shader = Shader("Resources\\Shaders\\BoxColor.glsl");
	//Inits camera
	cam = Camera(fVec2(DEFAULT_RESOLUTION_X, DEFAULT_RESOLUTION_Y), fVec3(0.0, 1250.0, 731.0), fVec2(0.0, -31.0));
	cam.Use();
	//Loads texture
	Image   im = Image("Resources\\Images\\TexturePackHex\\GrassHex.png");
	tex = Texture(im);
	im.Clear();
	//Init Player
	player = Player();
	player.Start();
	//Inits map
	for (int i = 0; i < mapSize.x; ++i) {
		for (int j = 0; j < mapSize.z; ++j) {
			for (int k = 0 ; k < mapSize.y; ++k) {
				worldMap.emplace_back(UnitHex(&shader, &tex));
				worldMap.back().position = fVec3(i, k, -j);
			}
		}
	}
}

void Demo::BlockInFrontOfCam() {
	
	fVec3 vRayStart = Camera::activeCam->__position;
	fVec3 vRayDir = Maths::SphericalToCartesian(Camera::activeCam->__rotation); //VecteurRegarde de la Cam forward (dx,dy,dz)
	
	fVec3 vRayUnitStepSize = fVec3(sqrt(1 + pow((vRayDir.y / vRayDir.x),2) + pow((vRayDir.z / vRayDir.x),2)) ,
		sqrt(1 + pow((vRayDir.x / vRayDir.y),2) + pow((vRayDir.z / vRayDir.y),2)), 
		sqrt(1 + pow((vRayDir.x / vRayDir.z),2) + pow((vRayDir.y / vRayDir.z),2)) );
	iVec3 vMapCheck = iVec3( vRayStart.x, vRayStart.y, vRayStart.z ); //troncature float to int
	fVec3 vRayLength1D;
	iVec3 vStep;

	//Config vStep & vRayLength1D
	if (vRayDir.x < 0) {
		vStep.x = -1;
		vRayLength1D.x = (vRayStart.x - float(vMapCheck.x)) * vRayUnitStepSize.x;
	}
	else {
		vStep.x = 1;
		vRayLength1D.x = (float(vMapCheck.x + 1) - vRayStart.x) * vRayUnitStepSize.x;
	}
	if (vRayDir.y < 0) {
		vStep.y = -1;
		vRayLength1D.y = (vRayStart.y - float(vMapCheck.y)) * vRayUnitStepSize.y;
	}
	else {
		vStep.y = 1;
		vRayLength1D.y = (float(vMapCheck.y + 1) - vRayStart.y) * vRayUnitStepSize.y;
	}
	if (vRayDir.z < 0) {
		vStep.z = -1;
		vRayLength1D.z = (vRayStart.z - float(vMapCheck.z)) * vRayUnitStepSize.z;
	}
	else {
		vStep.z = 1;
		vRayLength1D.z = (float(vMapCheck.z + 1) - vRayStart.z) * vRayUnitStepSize.z;
	}

	bool blockFound = false;
	float fDistance = 0.0f;
	float fMaxDistance = 100.0f;

	while (!blockFound && fDistance < fMaxDistance) {
		if (vRayLength1D.x < vRayLength1D.y)
		{
			if (vRayLength1D.x < vRayLength1D.z) {
				vMapCheck.x += vStep.x;
				fDistance = vRayLength1D.x;
				vRayLength1D.x += vRayUnitStepSize.x;
			}
			else if (vRayLength1D.x > vRayLength1D.z) {
				vMapCheck.z += vStep.z;
				fDistance = vRayLength1D.z;
				vRayLength1D.z += vRayUnitStepSize.z;
			}
			else {
				vMapCheck.x += vStep.x;
				vMapCheck.z += vStep.z;

				fDistance = vRayLength1D.x + vRayLength1D.z; // ?????????????? jsp

				vRayLength1D.x += vRayUnitStepSize.x;
				vRayLength1D.z += vRayUnitStepSize.z;
			}
		}
		else if (vRayLength1D.x > vRayLength1D.y) {
			if (vRayLength1D.y < vRayLength1D.z) {
				vMapCheck.y += vStep.y;
				fDistance = vRayLength1D.y;
				vRayLength1D.y += vRayUnitStepSize.y;
			}
			else if (vRayLength1D.y > vRayLength1D.z) {
				vMapCheck.z += vStep.z;
				fDistance = vRayLength1D.z;
				vRayLength1D.z += vRayUnitStepSize.z;
			}
			else {
				vMapCheck.y += vStep.y;
				vMapCheck.z += vStep.z;

				fDistance = vRayLength1D.y + vRayLength1D.z; // ?????????????? jsp

				vRayLength1D.y += vRayUnitStepSize.y;
				vRayLength1D.z += vRayUnitStepSize.z;
			}
		}
		else {
			if (vRayLength1D.y < vRayLength1D.z) {
				vMapCheck.x += vStep.x;
				vMapCheck.y += vStep.y;

				fDistance = vRayLength1D.x + vRayLength1D.y; // ?????????????? jsp

				vRayLength1D.x += vRayUnitStepSize.x;
				vRayLength1D.y += vRayUnitStepSize.y;
			}
			else if (vRayLength1D.y > vRayLength1D.z) {
				vMapCheck.z += vStep.z;
				fDistance = vRayLength1D.z;
				vRayLength1D.z += vRayUnitStepSize.z;
			}
			else {
				vMapCheck.x += vStep.x;
				vMapCheck.y += vStep.y;
				vMapCheck.z += vStep.z;

				fDistance = vRayLength1D.x + vRayLength1D.y +vRayLength1D.z; // ?????????????? jsp

				vRayLength1D.x += vRayUnitStepSize.x;
				vRayLength1D.y += vRayUnitStepSize.y;
				vRayLength1D.z += vRayUnitStepSize.z;
			}
		}
		
		//BlockFound ?
		/*if (vMapCheck.x >= 0 && vMapCheck.x < mapSize.x
			&& vMapCheck.y >= 0 && vMapCheck.y < mapSize.y
			&& vMapCheck.z >= 0 && vMapCheck.z < mapSize.z) {
			for (UnitHex& unit : worldMap) {
				fVec3 worldPos = CoordinateSystem::HexToWorld(unit.position, unit.size);
				iVec3 iworldPos = iVec3(worldPos.x, worldPos.y, worldPos.z);
				if (iworldPos == vMapCheck) {
					blockFound = true;
					std::cout <<" ///////////" << blockFound << " /////////////";
				}
			}
		}*/
		std::cout << vMapCheck.x << "," << vMapCheck.y << "," << vMapCheck.z << " ;";
		//std::cout << vMapCheck.x << "," << vMapCheck.y << "," << vMapCheck.z << "  // ";
	}
}

void Demo::Update() {
	tex.Bind();
	shader.Use();

	shader.SetUniform(GLSLDataType::Float3, "uCamPosition",      { &Camera::activeCam->__position });
	shader.SetUniform(GLSLDataType::Float3, "uLightSource",      { &lightPosition});
	shader.SetUniform(GLSLDataType::Float,  "uSpecularStrength", { &specularStrength });
	shader.SetUniform(GLSLDataType::Float,  "uSpecularPower",    { &specularPower });

	ImGui::Begin("DirectionalLightProperties");

		ImGui::DragFloat3("Light position",	  &lightPosition.x);
		ImGui::DragFloat("Specular Strength", &specularStrength);
		ImGui::DragFloat("Specular Power",    &specularPower);

	ImGui::End();

	player.Update();

	for (UnitHex& unit : worldMap) {
		unit.Draw();
	}
	BlockInFrontOfCam();
}