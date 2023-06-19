#include "Context.h"
#include "Shapes.h"
#include "log.h"
#include "Gui.h"
#include "FPS.h"
#include "Camera.h"
#include "Demo.h"
#include "Batch.h"
#include <vector>

//#include "Noise.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb\\stb_image.h"
//#include "stb\\stb_image_write.h"


static std::vector<fVec3> mapTest = {};

int main() {


	//uint8* img = new uint8[1000*1000*4];

	//int inc = 0;
	//for (int i = 0; i < 1000; ++i) {
	//	for (int j = 0; j < 1000; ++j) {
	//		float c    = Noise::FBM(fVec2(i, j) * (1.0f / 1000.0f) * 1.0);
	//		uint8 col  = c * 255;
	//		img[inc++] = col;
	//		img[inc++] = col;
	//		img[inc++] = col;
	//		img[inc++] = 255;
	//	}
	//}

	//stbi_write_png("FBM.png", 1000, 1000, 4, img, 1000*4);
	//delete[] img;

	if (!Context::Init(DEFAULT_RESOLUTION_X, DEFAULT_RESOLUTION_Y))
		return 0;
	Context::EnableDepthTest(1);
	Shape::Init();
	Gui::Init();

	Demo demo = Demo();
	while (!Context::shouldTerminate) {
		FPS::BeginFPSCalc();
		Gui::Begin();

		//Begins update
		ImGui::Begin("Debug");

		ImGui::Text("FPS:%lf", FPS::fps);
		ImGui::Text("DeltaTime:%lf", FPS::averageDeltaTime);

		ImGui::End();
		Context::Clear(0.04,0.04,0.1);
		demo.Update();

		Batch::Update();
		Batch::DrawAll();

		//EndUpdate
	    Gui::End();
		Context::Update();
		FPS::EndFPSCalc();
	}

	Shape::Destroy();
	Gui::Destroy();
	Context::Destroy();
} 