#pragma once
#include "App.h"
class Menu
{
	RenderWindow window;
	Camera camera;
	TextManager textManager;
	SoundsManager soundManager;
	BG background;
	int mode;
	bool sounds = 1;
	bool music = 1;
	bool aaMode = 1;
	bool smoothTextures = 1;
	bool fpsMode = 0;
	string lastTextSelected;
	Music MenuMusic;
public:
	Menu()
		: background(MenuMusic)
	{

	}
	void StartGame();
	void Start();
	bool TextTouch(string textName);
	bool UpdateText();
	void Update();
};

