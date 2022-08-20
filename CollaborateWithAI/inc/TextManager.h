#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
using namespace sf;
using namespace std;
class TextManager
{

public:
	unordered_map<string, Text> texts;
	unordered_map<string, Font> fonts;
	enum Origin
	{
		Left, 
		Middle,
		Right
	};
	Text& operator[](const string& index)
	{
		return texts[index];
	}
	void deleteAllData()
	{
		texts.erase(texts.begin(), texts.end());
		fonts.erase(fonts.begin(), fonts.end());
	}
	bool AddFont(string location, string name)
	{
		Font font;
		if (!font.loadFromFile(location))
			exit(0);
		fonts[name] = font;
		return 1;
	}
	void setOrigin(string name, Origin origin)
	{
		switch (origin)
		{
		case Left:
			texts[name].setOrigin(0, texts[name].getLocalBounds().height / 2);
			break;
		case Middle:
			texts[name].setOrigin(texts[name].getLocalBounds().width / 2, texts[name].getLocalBounds().height / 2);
			break;
		case Right:
			texts[name].setOrigin(texts[name].getLocalBounds().width, texts[name].getLocalBounds().height / 2);
			break;
		}
	}
	void AddText(string name)
	{
		Text text;
		texts[name] = text;
	}
	Font& getFont(string name)
	{
		return fonts[name];
	}
	Text& getText(string name)
	{
		return texts[name];
	}
	void SetupText(string name, float charSize, Color color, Font& font, Vector2f pos, string text1, Text::Style style)
	{
		texts[name].setCharacterSize(charSize);
		Texture& texture = const_cast<Texture&>(font.getTexture(charSize));
		texture.setSmooth(false);
		texts[name].setFillColor(color);
		texts[name].setFont(font);
		texts[name].setPosition(pos);
		texts[name].setString(text1);
		texts[name].setStyle(style);
		texts[name].setOrigin(texts[name].getLocalBounds().width / 2, texts[name].getLocalBounds().height / 2);
	}
};