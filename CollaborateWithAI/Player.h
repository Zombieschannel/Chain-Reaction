#pragma once
#include "User.h"
#include "inc/InputEvent.h"
#include "inc/Time.h"
#include "Bullet.h"
class Player : public User
{

	bool mcHold;
	SoundsManager& sounds;
	virtual void Start();
	ParticleSystem& playerTrail;
	ParticleSystem& bulletTrail;
	ParticleSystem& bulletExplode;
public:
	Player(SoundsManager& sounds1, ParticleSystem& playerTrail1, ParticleSystem& bulletTrail1, ParticleSystem& bulletExplode1)
		:sounds(sounds1), playerTrail(playerTrail1), bulletTrail(bulletTrail1), bulletExplode(bulletExplode1)
	{

	}
	Vector2f acc;
	Bullet bullet[c_playerMaxBullets];
	int usingBullets;
	float playerMaxSpeed;
	void Update(RenderWindow& window, View& cameraView);
	~Player()
	{

	}
};

