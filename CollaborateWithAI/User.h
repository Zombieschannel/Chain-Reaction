#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "inc/TextureManager.h"
#include "const.h"
using namespace sf;
using namespace std;
class User : public Drawable
{
public:
	RectangleShape player;
	TextureManager* textureManager;
	int hp;
	bool active;
	virtual ~User() {};

	void Setup(TextureManager* textureManager);
	virtual void Start() = 0;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

