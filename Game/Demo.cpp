#include "Demo.h"
#include "UnitHex.h"
#include "Camera.h"
#include "Texture.h"
#include "Player.h"
#include "CoordinateSystem.h"
#include <iostream>

#include "imgui/imgui.h"
#include "Noise.h"

#include <deque>

static 	Shader shader;
static Texture tex;
static float specularStrength = 0.0f;
static float specularPower    = 256.0f;
static Player player;
static iVec3 mapSize          = iVec3(60, 20, 60);
static fVec3 lightPosition;
static Camera cam;

//using std::size;
using std::cout;
using std::deque;
std::deque<UnitHex> worldMap;
int randomint = (rand() % (20 - 0 + 1)) + 0;

static UnitHex tt;

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
	tt  = UnitHex(&shader, &tex);
	for (int i = 0; i < mapSize.x; ++i) {
		for (int j = 0; j < mapSize.z; ++j) {
			int ee = tt.hauteur * Noise::FBMWrap(fVec2(i, j) * (1.0f / 1000.0f) * 1.0);
			for (int k = 0; k < ee; ++k) {
				worldMap.emplace_back(UnitHex(&shader, &tex));
				worldMap.back().position = fVec3(i, k, -j);
			}
		}
	}
}

bool Demo::BlockPresent(fVec3 Position) {
	fVec3 PositionHex = CoordinateSystem::WorldToHex(Position, tt.size);
	for (int i = 0; i < worldMap.size(); i++) {
		if (worldMap[i].position == PositionHex) {
			return true;
		}
	}
	return false;
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
		ImGui::DragFloat3("Player Position",   &player.position.x);
		fVec3 temp = CoordinateSystem::WorldToHex(player.position, tt.size);
		ImGui::DragFloat3("PlayerHexCoord: ", &temp.x);
		int bp = BlockPresent(player.position);
		ImGui::DragInt("BlockPresent: ", &bp);

		/*ImGui::DragFloat3("Rand Position", &worldMap[randomint].position.x);
		fVec3 temprand = CoordinateSystem::WorldToHex(worldMap[randomint].position, tt.size);
		ImGui::DragFloat3("Rand HexCoord: ", &temprand.x);
		fVec3 afterrand=CoordinateSystem::HexToWorld(temprand, tt.size);
		ImGui::DragFloat3("Rand Position After", &afterrand.x);
		fVec3 apresapresrand= CoordinateSystem::WorldToHex(afterrand, tt.size);
		ImGui::DragFloat3("Rand Position After", &apresapresrand.x);*/


	ImGui::End();

	tt.Draw(lightPosition);

	player.Update();

	lightPosition = player.position;

	for (int i = 0; i < worldMap.size(); i++) {
		fVec3 vPos = worldMap[i].position;
		if (abs(vPos.x) < mapSize.x / 2 && abs(vPos.z) < mapSize.z / 2) {
			worldMap[i].Draw();
		}
	}
}