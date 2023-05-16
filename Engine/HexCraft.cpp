#include "Context.h"
#include "Shapes.h"
#include "Shader.h"
#include "log.h"
#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"
#include <glew.h>
#include <glfw3.h>

int main() {

	if (!Context::Init(DEFAULT_RESOLUTION_X, DEFAULT_RESOLUTION_Y))
		return 0;

	Shapes::Init();
	Shader shader = Shader("Resources\\Shaders\\Color.shader");
	Camera cam    = Camera(fVec2(DEFAULT_RESOLUTION_X, DEFAULT_RESOLUTION_Y), fVec3(0.0, 0.0, 1.0));
	cam.Use();


	float angle = 0.0f;
	while (!Context::shouldTerminate) {
		 bool up   = glfwGetKey((GLFWwindow*)Context::window, 265) == GLFW_PRESS;
		 bool down = glfwGetKey((GLFWwindow*)Context::window, 264) == GLFW_PRESS;
		 angle     += (up - down);
		 
		 glm::vec3 t = glm::vec3(0.0, 0.0, -2.0);
		 glm::mat4 model = glm::translate(glm::mat4(1.0), t);
		 model = glm::rotate(model, Maths::DegToRad(angle), glm::vec3(1.0, 0.0, 0.0));

		 shader.Use();
		 //shader.SetUniform(GLSLDataType::Float3, "uModel", { &t });
		 glm::mat4 temp = cam.activeCam->VP * model;
		 shader.SetUniform(GLSLDataType::Mat4f, "uMVP", { &temp[0][0] });


		 if (glGetError()) 
			 printf("Error");
		 Context::Clear(0.2,0.2,0.3);
		 Quad::instance.Draw();
		 Context::Update();
	}
	Context::Destroy();
}