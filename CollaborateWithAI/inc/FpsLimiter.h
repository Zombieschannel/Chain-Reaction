#pragma once
#include <SFML/Graphics.hpp>
#include "Time.h"
using namespace sf;
#define deltaFps 10
class FPS
{
	int fps;
public:
	static FPS& Get()
	{
		static FPS instance;
		return instance;
	}
	static void setFrameRateLimit(int fps)
	{
		Get().fps = fps;
	}
	static void LimitFPS()
	{	
		TimeManager::setTLimit();
		if (TimeManager::getClock().asMicroseconds() < 1000000.0 / Get().fps)
			sleep(microseconds(1000000.0 / Get().fps - TimeManager::getClock().asMicroseconds()));
		TimeManager::Restart();
	}
};
