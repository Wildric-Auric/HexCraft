#include "Context.h"
#include "Shapes.h"
#include "Shader.h"
#include "log.h"
#include "Camera.h"
#include "Gui.h"

#include "glm/gtc/matrix_transform.hpp"
#include <glew.h>
#include <glfw3.h>

int main() {

	if (!Context::Init(DEFAULT_RESOLUTION_X, DEFAULT_RESOLUTION_Y))
		return 0;
	Context::EnableDepthTest(1);


	Shape::Init();
	Gui::Init();

	Shader shader  = Shader("Resources\\Shaders\\BoxColor.shader");
	Shader shader2 = Shader("Resources\\Shaders\\BoxColor.shader");

	Camera cam    = Camera(fVec2(DEFAULT_RESOLUTION_X, DEFAULT_RESOLUTION_Y), fVec3(0.0, 0.0, 0.0));
	cam.Use();

	fVec3 scale	   = fVec3(200.0, 200.0, 1.0);
	fVec3 position = fVec3(0.0, 0.0, -DEFAULT_ORTHO_PLANE * 2.0);
	fVec3 rotation = fVec3(0.0, 0.0, 0.0);
		
	while (!Context::shouldTerminate) {
		Gui::Begin();

		ImGui::Begin("Debug");
		ImGui::DragFloat3("Scale", &scale.x);
		ImGui::DragFloat3("Position", &position.x);
		ImGui::DragFloat3("Rotation", &rotation.x);
		ImGui::End();
		 
		 if (glGetError()) 
			 printf("Error");

		 Context::Clear(0.04,0.04,0.1);

		 glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(position.x, position.y, position.z));

		 model = glm::rotate(model, Maths::DegToRad(rotation.x), glm::vec3(1.0,0.0,0.0));
		 model = glm::rotate(model, Maths::DegToRad(rotation.y), glm::vec3(0.0,1.0,0.0));
		 model = glm::rotate(model, Maths::DegToRad(rotation.z), glm::vec3(0.0,0.0,1.0));

	     model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
		 shader.Use();
		 glm::mat4 temp = cam.activeCam->VP * model;
		 shader.SetUniform(GLSLDataType::Mat4f, "uMVP", { &temp[0][0] });

		 Cube::instance.Draw();

		 Gui::End();
		 Context::Update();
	}

	Shape::Destroy();
	Gui::Destroy();
	Context::Destroy();
}