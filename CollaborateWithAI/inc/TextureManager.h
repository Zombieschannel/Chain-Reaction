#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
using namespace sf;
using namespace std;
//v.1.1
class TextureManager
{
	unordered_map<string, Texture> textures;
public:
	Texture& operator[](const string& index)
	{
		return textures[index];
	}
	void deleteAllData()
	{
		textures.erase(textures.begin(), textures.end());
	}
	bool AddTexture(string location, string name)
	{
		Texture a;
		if (!a.loadFromFile(location))
			exit(0);
		textures[name] = a;
		return 1;
	}
	bool AddTexture(Image& image, string name)
	{
		Texture a;
		if (!a.loadFromImage(image))
			exit(0);
		textures[name] = a;
		return 1;
	}
	Texture& getTexture(string name)
	{
		return textures[name];
		exit(0);
	}
	void setAllSmooth(bool Bool)
	{
		for (auto& n : textures)
			textures[n.first].setSmooth(Bool);
	}
	void setSmooth(string name, bool Bool)
	{
		textures[name].setSmooth(Bool);
	}
	void setAllRepeated(bool Bool)
	{
		for (auto& n : textures)
			textures[n.first].setRepeated(Bool);
	}
	void setRepeated(string name, bool Bool)
	{
		textures[name].setRepeated(Bool);
	}
	void setAllSrgb(bool Bool)
	{
		for (auto& n : textures)
			textures[n.first].setSrgb(Bool);
	}
	void setSrgb(string name, bool Bool)
	{
		textures[name].setSrgb(Bool);
	}
};