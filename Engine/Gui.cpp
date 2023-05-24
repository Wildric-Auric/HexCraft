#include "glew.h"
#include "glfw3.h"
#include "Context.h"

#include "Gui.h"

void Gui::Init() {
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Context::window, true);
	ImGui_ImplOpenGL3_Init();
	static ImGuiIO& io = ImGui::GetIO();
	//ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.Fonts->AddFontFromFileTTF("Resources\\fonts\\arial.ttf", 16.0f);
}

void Gui::Begin() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Gui::End() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::Destroy() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}