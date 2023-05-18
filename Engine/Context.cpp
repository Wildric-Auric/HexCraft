#include "glew.h"
#include "glfw3.h"
#include "Context.h"
#include "log.h"

void* Context::window            = nullptr;
int   Context::__width           = 0;
int   Context::__height		     = 0;
int   Context::vSync			 = 1;
int   Context::shouldTerminate   = 0;

void WindowSizeCallBack(GLFWwindow* window, int width, int height) {
	Context::__width  =	width;
	Context::__height = height;
}

uint32 Context::__depthTestMask = 0;

void Context::EnableDepthTest(bool status) {
	if (status) {
		Context::__depthTestMask = GL_DEPTH_BUFFER_BIT;
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		return;
	}
	Context::__depthTestMask = 0;
	glDisable(GL_DEPTH_TEST);
}

bool Context::Init(int width, int height) {

	Context::__width =	width;
	Context::__height = height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Maybe 4 later for compute shaders
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Temporary multisampling, main framebuffer multisampling, would need to do it offscreen later
	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);

	Context::window = (void*)glfwCreateWindow(width, height,"HexCraft", NULL, NULL);
	if (Context::window == nullptr) {
		const char* buffer = "";
		glfwGetError(&buffer);
		LOG("GLFW error during initialisation. Error details: ");
		LOG(buffer);
		return 0;
	}
	glfwMakeContextCurrent((GLFWwindow*)Context::window);
	glfwSetFramebufferSizeCallback((GLFWwindow*)Context::window, WindowSizeCallBack);

	if (glewInit() != GLEW_OK) {
		LOG("Error during glew initialization");
		return 0;
	}

	glEnable(GL_CULL_FACE);  //glFrontFace(GL_FRONT) is default setting

	return 1;
}

void Context::Clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	GLbitfield mask = GL_COLOR_BUFFER_BIT;
	mask |= Context::__depthTestMask;
	glClear(mask); //TODO::Add Dynamic clearing for depth buffer and stencil buffer if enabled
}

void Context::Update() {
	glfwSwapInterval(Context::vSync);
	glfwSwapBuffers((GLFWwindow*)window);
	glfwPollEvents();
	Context::shouldTerminate = glfwWindowShouldClose((GLFWwindow*)Context::window);
}

void Context::Destroy() {
	glfwTerminate();
}




