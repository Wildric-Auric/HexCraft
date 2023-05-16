#include "Context.h"
#include "Shapes.h"
#include "Shader.h"
#include "log.h"
#include <glew.h>
#include <glfw3.h>

int main() {

	if (!Context::Init(720, 720))
		return 0;

	Shapes::Init();
	Shader shader = Shader("Resources\\Shaders\\Color.shader");
	shader.Use();
	while (!Context::shouldTerminate) {
		 Context::Clear();
		 int a = 0;
		 if (a = glGetError()) 
			 std::cout << a << std::endl;
		 shader.Use();
		 Quad::instance.Draw();

		 Context::Update();
	}
	Context::Destroy();
}