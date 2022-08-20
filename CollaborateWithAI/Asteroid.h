#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "const.h"
#include "inc/Time.h"
#include "inc/Collisions.h"
#include "inc/TextureManager.h"
using namespace sf;
using namespace std;
class Asteroids : public Drawable
{
	friend class App;
	struct Asteroid
	{
		bool active;
		CircleShape shape;
		CircleShape shadow;
		Vector2f targetPos;
		int id;
		int rotateSpeed;
	};
	vector<Asteroid> asteroids;
	double asteroidSpawnRate;
public:
	void Start(TextureManager& textures);
	void Update(View& cameraView);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

