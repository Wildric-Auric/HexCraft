#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class Gui {
public:
	static void Init();
	static void Begin();
	static void End();
	static void Destroy();
};