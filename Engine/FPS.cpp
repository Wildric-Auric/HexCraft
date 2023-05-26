#include "FPS.h"
#include "glfw3.h"

int    FPS::currentFrame                     = 0;
double FPS::lastFrames[frameNumForAverage]   = {0.0};
double FPS::fps                              = 60.0f;
double FPS::deltaTime						 = 0.016f;
double FPS::averageDeltaTime                 = 0.016f;

static double tempTime    =	0.0f;
static double cummulation = 0.0f;

void FPS::BeginFPSCalc() {
	tempTime = glfwGetTime();
}

void FPS::EndFPSCalc() {
	FPS::deltaTime             = glfwGetTime() - tempTime;	
	lastFrames[currentFrame++] = FPS::deltaTime;
	cummulation               += FPS::deltaTime;
	currentFrame			  %= frameNumForAverage;
	//Update fps
	if (currentFrame == 0) {
		FPS::averageDeltaTime  = cummulation        / frameNumForAverage;
		FPS::fps               = frameNumForAverage / cummulation;
		cummulation = 0.0f;
	}
}
