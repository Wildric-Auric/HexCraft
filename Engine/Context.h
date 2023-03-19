#pragma once


class Context {
public:
	static void* window;
	static int __width; //ReadOnly
	static int __height; 
	static int shouldTerminate;
	static int	vSync;
	static bool Init(int width = 640, int height = 480);
	static void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f );
	static void Update();
	static void Destroy();
};