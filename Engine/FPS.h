#pragma once

const int frameNumForAverage = 15;


class FPS {
public:
	static int currentFrame;
	static double lastFrames[frameNumForAverage];
	static double fps;
	static double deltaTime;
	static double averageDeltaTime;
	static void BeginFPSCalc();
	static void EndFPSCalc();
};