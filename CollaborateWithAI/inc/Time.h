#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
class TimeManager
{
	vector<Clock> clocks;
	vector<bool> restartWithDelta;
	Clock delta;
	Time lastTime;
	Time Tlimit;
	TimeManager() {};
	static TimeManager& Get()
	{
		static TimeManager instance;
		return instance;
	}
public:
	TimeManager(const TimeManager&) = delete;
	
	static void addClock(Clock clock1, bool restart) { Get().clocks.push_back(clock1); Get().restartWithDelta.push_back(restart); }
	static Clock getClock(int id) { return Get().clocks[id]; }
	static void restartClock(int id) { Get().clocks[id].restart(); }
	static Time getClock() { return Get().delta.getElapsedTime(); };
	static void Restart()
	{
		Get().lastTime = Get().delta.getElapsedTime();
		Get().delta.restart();
		for (int a = 0; a < Get().clocks.size(); a++)
			if (Get().restartWithDelta[a])
				Get().clocks[a].restart();
	}
	//get theoretical frame rate limit
	static void setTLimit()
	{
		Get().Tlimit = Get().delta.getElapsedTime();
	}
	//get theoretical frame rate limit
	static Time getTLimit() { return Get().Tlimit; }
	static Time getDeltaTime() { return Get().lastTime; }
	static int getFrameRate() { return 1 / Get().lastTime.asSeconds(); }
};