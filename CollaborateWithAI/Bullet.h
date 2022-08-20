#pragma once
#include <SFML/Graphics.hpp>
#include "const.h"
#include "inc/InputEvent.h"
#include "inc/Time.h"
#include "inc/TextureManager.h"
#include "inc/Collisions.h"
using namespace sf;
class Bullet : public Drawable
{
	friend class App;

	Vector2f targetLocation;
	Vector2f additionalDir;


	int speed;


public:
	const Vector2f* targetPos;
	float lifeTime;
	bool doNotDrawBeam;
	int beamTargetID;
	int hitCnt;
	CircleShape bullet;
	float bulletRecharge;
	RectangleShape beam;
	bool active;
	void Start(TextureManager& textures);
	void Delete();
	void Spawn(Vector2f additionalDir, Vector2f location, float angle);
	void Bounce(float angle, const Vector2f* targetPos);
	void Update(ParticleSystem& bulletExplode);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

