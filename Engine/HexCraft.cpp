#include "Context.h"
#include "Shapes.h"
#include "Shader.h"
#include "log.h"
#include "Camera.h"
#include "Gui.h"
#include "Texture.h"
#include "FPS.h"

#include "glm/gtc/matrix_transform.hpp"


#include <vector>



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
			//float r = ((double)std::rand()  / (double)(RAND_MAX)) + 1;
			int y = -2000.0 + 1000.0;
			mapTest.push_back(fVec3(x,y, -z));
		}
	}

	Shape::Init();
	Gui::Init();
	
	Shader shader  = Shader("Resources\\Shaders\\BoxColor.glsl");
	Shader shader2 = Shader("Resources\\Shaders\\Color.glsl");

	Camera cam		  = Camera(fVec2(DEFAULT_RESOLUTION_X, DEFAULT_RESOLUTION_Y), fVec3(0.0, 1250.0, 731.0), fVec2(0.0, -31.0));
	Camera::activeCam = &cam;
	cam.Use();

	fVec3 scale	   = fVec3(200.0, 200.0, 200.0);
	fVec3 position = fVec3(0.0, 1250.0,-731.0);
	fVec3 rotation = fVec3(0.0, 0.0, 0.0);

	fVec3 cameraPosition = cam.__position;
	fVec2 cameraRotation = fVec2(Maths::RadToDeg(cam.__rotation.x), Maths::RadToDeg(cam.__rotation.y));

	Image   im  = Image("Resources\\Images\\TexturePackHex\\WoodHex.png");
	Texture tex = Texture(im);

	float specularStrength = 0.0f;
	float specularPower    = 256.0f;

	tex.Bind();

	while (!Context::shouldTerminate) {
		FPS::BeginFPSCalc();



		Gui::Begin();

		ImGui::Begin("Debug");

		ImGui::Text("FPS:%lf", FPS::fps);
		ImGui::Text("DeltaTime:%lf", FPS::averageDeltaTime);

		ImGui::DragFloat3("Scale", &scale.x);
		ImGui::DragFloat3("Position", &position.x);
		ImGui::DragFloat3("Rotation", &rotation.x);
		ImGui::DragFloat( "Specular strength"        , &specularStrength);
		ImGui::DragFloat( "Specular Power"           , &specularPower);

		bool a = ImGui::DragFloat3("CamPosition", &cameraPosition.x);
		bool b = ImGui::DragFloat2("CamRotation", &cameraRotation.x);
		if (a || b) {
			cam.UpdateTranform(cameraPosition, cameraRotation);
		}


		ImGui::DragFloat("UnitX", &unitX);
		ImGui::DragFloat("UnitY", &unitY);
		ImGui::DragFloat("UnitZ", &unitZ);
		

		ImGui::End();

		 Context::Clear(0.04,0.04,0.1);

		 shader.Use();

		 glm::mat4 model = glm::mat4(1.0);
		 model = glm::translate(model, glm::vec3(position.x, position.y, position.z));

		 model = glm::rotate(model, Maths::DegToRad(rotation.x), glm::vec3(1.0,0.0,0.0));
		 model = glm::rotate(model, Maths::DegToRad(rotation.y), glm::vec3(0.0,1.0,0.0));
		 model = glm::rotate(model, Maths::DegToRad(rotation.z), glm::vec3(0.0,0.0,1.0));

		 model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
		
		 glm::mat4 temp = cam.activeCam->VP;
		
		 shader.SetUniform(GLSLDataType::Mat4f, "uVP",	  { &temp[0][0] });
		 shader.SetUniform(GLSLDataType::Mat4f, "uModel", { &model[0][0]});

		 shader.SetUniform(GLSLDataType::Float3, "uCamPosition", {&cam.__position});
		 shader.SetUniform(GLSLDataType::Float3, "uLightSource", {&position});

		 shader.SetUniform(GLSLDataType::Float, "uSpecularStrength", {&specularStrength});
		 shader.SetUniform(GLSLDataType::Float, "uSpecularPower", {&specularPower});
		 
		 HexaPrism::instance.Draw();

		 //Drawing the map
		 for (int i = 0; i < 30; i++) {
			 for (int j = 0; j < 30; ++j) {
				float x = i * unitX * 0.75;
				float z = j * unitZ;
				if (i % 2) z += unitZ * 0.5;
				//float r = ((double)std::rand()  / (double)(RAND_MAX)) + 1;
				int y = -2000.0;
				// mapTest.push_back(fVec3(x, y, -z));
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(x, y, -z));
				model = glm::scale(model, glm::vec3(unitX, unitY, unitZ));
				glm::mat4 temp = cam.activeCam->VP;
				shader.SetUniform(GLSLDataType::Mat4f, "uVP",    { &temp[0][0]  });
				shader.SetUniform(GLSLDataType::Mat4f, "uModel", { &model[0][0] });
				HexaPrism::instance.Draw();
			 }
		 }

		 Gui::End();
		 Context::Update();


		 FPS::EndFPSCalc();
	}

	Shape::Destroy();
	Gui::Destroy();
	Context::Destroy();
} 