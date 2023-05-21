#include "Context.h"
#include "Shapes.h"
#include "Shader.h"
#include "log.h"
#include "Camera.h"
#include "Gui.h"
#include <vector>

#include "glm/gtc/matrix_transform.hpp"


static std::vector<fVec3> mapTest = {};

int main() {

	if (!Context::Init(DEFAULT_RESOLUTION_X, DEFAULT_RESOLUTION_Y))
		return 0;
	Context::EnableDepthTest(1);

	float unitX = 500.0;
	float unitZ = 500.0;
	float unitY = 1000.0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; ++j) {
			float x = i * unitX * 0.75;
			float z = j * unitZ;
			if (i % 2) z += unitZ * 0.5;
			mapTest.push_back(fVec3(x,-2000.0f, -z));
		}
	}

	Shape::Init();
	Gui::Init();

	Shader shader  = Shader("Resources\\Shaders\\BoxColor.shader");
	Shader shader2 = Shader("Resources\\Shaders\\Color.shader");

	Camera cam    = Camera(fVec2(DEFAULT_RESOLUTION_X, DEFAULT_RESOLUTION_Y), fVec3(0.0, 0.0, 0.0));
	cam.Use();

	fVec3 scale	   = fVec3(200.0, 200.0, 200.0);
	fVec3 position = fVec3(0.0, 0.0, -DEFAULT_ORTHO_PLANE * 2.0);
	fVec3 rotation = fVec3(0.0, 0.0, 0.0);

	fVec3 cameraPosition = fVec3();
	fVec2 cameraRotation = fVec2();
		
	while (!Context::shouldTerminate) {
		Gui::Begin();

		ImGui::Begin("Debug");
		ImGui::DragFloat3("Scale", &scale.x);
		ImGui::DragFloat3("Position", &position.x);
		ImGui::DragFloat3("Rotation", &rotation.x);

		bool a = ImGui::DragFloat3("CamPosition", &cameraPosition.x);
		bool b = ImGui::DragFloat2("CamRotation", &cameraRotation.x);
		if (a || b) {
			cam.UpdateTranform(cameraPosition, cameraRotation);
		}

		ImGui::End();

		 Context::Clear(0.04,0.04,0.1);

		 shader.Use();

		 glm::mat4 model = glm::mat4(1.0);
		 model = glm::translate(model, glm::vec3(position.x, position.y, position.z));

		 model = glm::rotate(model, Maths::DegToRad(rotation.x), glm::vec3(1.0,0.0,0.0));
		 model = glm::rotate(model, Maths::DegToRad(rotation.y), glm::vec3(0.0,1.0,0.0));
		 model = glm::rotate(model, Maths::DegToRad(rotation.z), glm::vec3(0.0,0.0,1.0));

		 model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
		
		 glm::mat4 temp = cam.activeCam->VP * model;
		 shader.SetUniform(GLSLDataType::Mat4f, "uMVP", { &temp[0][0] });

		 HexaPrism::instance.Draw();

		 //Drawing the map
		 for (const fVec3& pos : mapTest) {
			 model = glm::mat4(1.0);
			 model = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));
			 model = glm::scale(model, glm::vec3(unitX, unitY, unitZ));
			 glm::mat4 temp = cam.activeCam->VP * model;
			 shader.SetUniform(GLSLDataType::Mat4f, "uMVP", { &temp[0][0] });

			 HexaPrism::instance.Draw();
		 }

		 Gui::End();
		 Context::Update();
	}

	Shape::Destroy();
	Gui::Destroy();
	Context::Destroy();
} 