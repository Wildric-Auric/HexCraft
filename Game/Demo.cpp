#include "Demo.h"
#include "UnitHex.h"
#include "Camera.h"
#include "Texture.h"
#include "Player.h"

#include "Noise.h"
#include "CoordinateSystem.h"
#include "Log.h"
#include "Batch.h"
#include "Shapes.h"

#include "imgui/imgui.h"
#include <deque>

#include "Map.h"
#include "ResourcesManager.h"

//Temporary
#include "Noise.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb\\stb_image.h"
#include "stb\\stb_image_write.h"
//------------------------

static 	Shader shader;
static  Shader shader0;
static Texture tex;
static float specularStrength = 0.0f;
static float specularPower    = 256.0f;
static Player player;
static iVec3 mapSize          = iVec3(50, 60, 50);
static fVec3 lightPosition;
static Camera cam;
static UnitHex tt;
static Texture tex2;

std::deque<UnitHex> worldMap;

static Map mapp;

Demo::Demo() {

	//uint8* img = new uint8[1000*1000*4];
    /*int inc = 0;
	for (int i = 0; i < 1000; ++i) {
		for (int j = 0; j < 1000; ++j) {
			float c    =  Noise::FBMWrap(fVec2(i, j) * (1.0f / 100.0f) * 2.0);
			uint8 col  = (uint8)(c * 255.0);
			img[inc++] = col;
			img[inc++] = col;
			img[inc++] = col;
			img[inc++] = 255;
		}
	}

	stbi_write_png("TEST.png", 1000, 1000, 4, img, 1000*4);
	delete[] img;*/


	cam = Camera(fVec2(DEFAULT_RESOLUTION_X, DEFAULT_RESOLUTION_Y), fVec3(0.0, 1250.0, 731.0), fVec2(0.0, -31.0));
	cam.Use();
	//Init Player
	player = Player();
	player.Start();

	//Should clean
	UnitHex::Init();
	Map* map = new Map();
	Map::current = map;
}



void Demo::Update() {
	LOG_OPENGL_ERROR();
	//tex.Bind();
	//shader0.Use();
	auto shader = Shader::ResourceMap.find(RES_SHADER_DIR "PrismBatched.glsl");
	if (shader == Shader::ResourceMap.end())
		LOG_WARNING("PrismBatched shader not found");
	else {
		shader->second.Use();
		shader->second.SetUniform(GLSLDataType::Float3, "uCamPosition",      { &Camera::activeCam->__position });
		shader->second.SetUniform(GLSLDataType::Float3, "uLightSource",      { &lightPosition});
		shader->second.SetUniform(GLSLDataType::Float,  "uSpecularStrength", { &specularStrength });
		shader->second.SetUniform(GLSLDataType::Float,  "uSpecularPower",    { &specularPower });
	}

	ImGui::Begin("DirectionalLightProperties");

		ImGui::DragFloat3("Light position",	  &lightPosition.x);
		ImGui::DragFloat("Specular Strength", &specularStrength);
		ImGui::DragFloat("Specular Power",    &specularPower);
		ImGui::DragFloat3("Player Position",   &player.position.x);
		fVec3 temp = CoordinateSystem::WorldToHex(player.position, tt.size);
		ImGui::DragFloat3("PlayerHexCoord: ", &temp.x);

	ImGui::End();

	player.Update();

	fVec3 pos;
	fVec3 dontDraw(10000.0, 10000.0, 10000.0);

	float step      = 1000.0;
	for (int i = 0; i < 20; i++) {
		pos              = player.position + player.forward.normalize() * step;
		step += 10000.0;
		fVec3 bloc       = CoordinateSystem::WorldToHex(pos, tt.size);
		float height     = 15.0 * Noise::FBMWrap(fVec2(bloc.x, bloc.z) * (1.0f / 1000.0f) * 1.0);
		if (bloc.y <= height) {
			dontDraw = bloc;
			break;
		}
	}

	lightPosition = player.position;
	mapp.Update(player.position);
	mapp.Draw();
}







