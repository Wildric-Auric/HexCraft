#include "Demo.h"
#include "UnitHex.h"
#include "Camera.h"
#include "Texture.h"
#include "Player.h"

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
}