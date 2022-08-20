#include "Menu.h"

void Menu::StartGame()
{
	App app(window, camera, soundManager, background, MenuMusic);
	app.sounds = sounds;
	app.music = music;
	app.smoothTextures = smoothTextures;
	app.Start();
}

void Menu::Start()
{
	srand(time(NULL));
	window.create(VideoMode(1280, 720), AppName, Style::Close, ContextSettings(0, 0, 4));
	window.setVerticalSyncEnabled(1);
	Image logo;
	logo.loadFromFile("Res/logo.png");
	window.setIcon(64, 64, logo.getPixelsPtr());
	//window.setFramerateLimit(60);
	InputEvent::Start(window);
	camera.setScaledAspectRatio(16.0 / 9, (Vector2f)window.getSize(), Vector2i(1280, 720));
	textManager.AddFont("Res/Uni_Sans_Heavy.otf", "Default");
	textManager.AddText("00");//title
	textManager.AddText("01");//play
	textManager.AddText("02");//settings
	textManager.AddText("03");//about
	textManager.AddText("04");//exit
	textManager.AddText("10");//settings
	textManager.AddText("11");//sounds
	textManager.AddText("12");//music
	textManager.AddText("13");//quality
	textManager.AddText("14");//back
	textManager.AddText("20");//about
	textManager.AddText("21");//about1
	textManager.AddText("22");//about2
	textManager.AddText("23");//about3
	textManager.AddText("24");//about4
	textManager.AddText("25");//back
	textManager.AddText("2v");//back
	mode = 0;

	MenuMusic.openFromFile("Res/Cursedsnake - Sunrays.ogg");
	MenuMusic.setVolume(5);
	MenuMusic.play();
	MenuMusic.setLoop(1);

	background.Start(camera);
	Vector2f allPos = Vector2f(camera.getSize().x / 10, camera.getSize().y / 10);
	textManager.SetupText("00", 80, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 2.5), AppName, Text::Style::Regular);
	textManager.SetupText("01", 50, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 4), "Play", Text::Style::Regular);
	textManager.SetupText("02", 40, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 5), "Settings", Text::Style::Regular);
	textManager.SetupText("03", 40, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 6), "About", Text::Style::Regular);
	textManager.SetupText("04", 40, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 7), "Exit", Text::Style::Regular);

	textManager.SetupText("10", 70, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 2.5), "Settings", Text::Style::Regular);
	textManager.SetupText("11", 40, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 4), "Sounds: on", Text::Style::Regular);
	textManager.SetupText("12", 40, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 5), "Music: on", Text::Style::Regular);
	textManager.SetupText("13", 40, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 6), "Quality: Best", Text::Style::Regular);
	textManager.SetupText("14", 40, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 7), "Back", Text::Style::Regular);

	textManager.SetupText("20", 70, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 2.5), "About", Text::Style::Regular);
	textManager.SetupText("21", 40, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 4), "Made with C++ and SFML for the: ", Text::Style::Regular);
	textManager.SetupText("22", 40, Color(255, 100, 100), textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 5), "Wowie Jam 4.0", Text::Style::Regular);
	textManager.SetupText("23", 40, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 6), "My YT channel: Zombieschannel", Text::Style::Regular);
	textManager.SetupText("24", 40, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 7), "Music: Sunrays by Cursedsnake", Text::Style::Regular);
	textManager.SetupText("25", 40, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 5, allPos.y * 8), "Back", Text::Style::Regular);
	textManager.SetupText("2v", 20, Color::White, textManager.getFont("Default"),
		Vector2f(allPos.x * 9.8, allPos.y * 9.7), "v.1.0", Text::Style::Regular);

	soundManager.AddSound("Res/Click.wav", "click", 1);
	soundManager.AddSound("Res/death.wav", "death", 1);
	soundManager.AddSound("Res/explosion1.wav", "ex1", 1);
	soundManager.AddSound("Res/explosion2.wav", "ex2", 1);
	soundManager.AddSound("Res/explosion3.wav", "ex3", 1);
	soundManager.AddSound("Res/hit.wav", "hit", 1);
	soundManager.AddSound("Res/Hover.wav", "hover", 1);
	soundManager.AddSound("Res/PowerUp.wav", "powerup", 1);
	soundManager.AddSound("Res/Shoot.wav", "shoot", 1);

	soundManager.ReloadAllSounds();
	soundManager.setVolumeAll(30);
	Update();
}

bool Menu::TextTouch(string textName)
{
	textManager.getText(textName).setStyle(Text::Style::Regular);
	if (lastTextSelected == textName && !textManager.getText(textName).getGlobalBounds().contains((Vector2f)window.mapPixelToCoords(InputEvent::getMousePosition(window))))
		lastTextSelected = "";
	if (textManager.getText(textName).getGlobalBounds().contains((Vector2f)window.mapPixelToCoords(InputEvent::getMousePosition(window))))
	{
		if (lastTextSelected != textName)
			soundManager.reset("hover");
		lastTextSelected = textName;
		textManager.getText(textName).setStyle(Text::Style::Underlined);
		if (InputEvent::isButtonReleased(Mouse::Left))
		{
			soundManager.reset("click");
			return 1;
		}
	}
	return 0;
}

bool Menu::UpdateText()
{
	switch (mode)
	{
	case 0:
		if (TextTouch("01"))
		{
			StartGame();
		}
		if (TextTouch("02"))
		{
			mode = 1;
		}
		if (TextTouch("03"))
		{
			mode = 2;
		}
		if (TextTouch("04"))
		{
			return 1;
		}
		break;
	case 1:
		if (TextTouch("11"))
		{
			sounds = !sounds;
			if (!sounds)
				soundManager.setVolumeAll(0);
			else
				soundManager.setVolumeAll(30);
			textManager["11"].setString("Sounds: " + (sounds ? (string)"on" : "off"));
			textManager.setOrigin("11", TextManager::Middle);
		}
		if (TextTouch("12"))
		{
			music = !music;
			if (!music)
				MenuMusic.setVolume(0);
			else
				MenuMusic.setVolume(5);
			textManager["12"].setString("Music: " + (music ? (string)"on" : "off"));
			textManager.setOrigin("12", TextManager::Middle);
		}
		if (TextTouch("13"))
		{
			aaMode = !aaMode;
			smoothTextures = !smoothTextures;
			textManager["13"].setString("Quality: " + (aaMode ? (string)"Best" : "Low"));
			if (aaMode)
			{
				background.DoNotUpdate = 0;
				window.create(VideoMode(1280, 720), AppName, Style::Close, ContextSettings(0, 0, 4));
				window.setVerticalSyncEnabled(1);
			}
			else
			{
				background.DoNotUpdate = 1;
				window.create(VideoMode(1280, 720), AppName, Style::Close, ContextSettings(0, 0, 0));
				window.setVerticalSyncEnabled(1);
			}
			Image logo;
			logo.loadFromFile("Res/logo.png");
			window.setIcon(64, 64, logo.getPixelsPtr());
			textManager.setOrigin("13", TextManager::Middle);
		}
		if (TextTouch("14"))
		{
			mode = 0;
		}
		break;
	case 2:
		if (TextTouch("22"))
		{
			system("start https://itch.io/jam/wowie-jam-4");
		}
		if (TextTouch("23"))
		{
			system("start https://www.youtube.com/channel/UCG2AUOl6FN6GHMQTL5DTAZw");
		}
		if (TextTouch("24"))
		{
			system("start https://www.youtube.com/c/Cursedsnake");
		}
		if (TextTouch("25"))
		{
			mode = 0;
		}
		break;
	}
	return 0;
}

void Menu::Update()
{
	while (window.isOpen())
	{
		Event event;
		InputEvent::OnceUpdate();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			InputEvent::EventUpdate(event);
		}
		if (InputEvent::isKeyReleased(Keyboard::Escape) || UpdateText())
			break;
		background.Update();

		if (InputEvent::isKeyReleased(Keyboard::F3))
		{
			fpsMode = !fpsMode;
			if (!fpsMode)
				window.setTitle(AppName);
		}

		window.clear();
		window.draw(background);

		for (auto& n : textManager.texts)
		{
			if (n.first[0] == mode + '0')
				window.draw(n.second);
		}
		window.display();
		if (fpsMode)
			window.setTitle("FPS: " + to_string(int(1 / TimeManager::getDeltaTime().asSeconds())));
		TimeManager::Restart();
	}
	
}
