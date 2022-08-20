#pragma once
#include <SFML/Graphics.hpp>
#include "inc/FpsLimiter.h"
#include "inc/InputEvent.h"
#include "inc/Time.h"
#include "inc/TextureManager.h"
#include "inc/Camera.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Asteroid.h"
#include "inc/TextManager.h"
#include "PowerUp.h"
#include "BG.h"
using namespace sf;
class App
{
	RenderWindow& window;
	SoundsManager& soundManager;
	bool gameOver = 0;
	Camera& camera;
	BG& bg;
	Music& MenuMusic;

	Player player;
	TextureManager textures;
	EnemyManager enemy;
	Asteroids asteroids;
	TextManager textManager;
	PowerUp powerUp;

	float moveEndScreen = 0;

	RectangleShape lifeIcon;
	RectangleShape boostIcon;


	int kills;
	float comboAlpha[c_playerMaxBullets];

	RectangleShape bulletRecharge[c_playerMaxBullets];

	bool fpsMode = 0;
	bool escMode = 0;

	ParticleSystem BulletTrail;
	ParticleSystem EnemyHit;
	ParticleSystem EnemySpawn;
	ParticleSystem EnemyTrail;
	ParticleSystem PlayerHit;
	ParticleSystem PlayerTrail;
	ParticleSystem PowerUpCollect;
	ParticleSystem BulletExplode;


public:
	bool sounds;
	bool music;
	bool smoothTextures;
	App(RenderWindow& window1, Camera& camera1, SoundsManager& sounds1, BG& bg1, Music& music1)
		: window(window1), camera(camera1), soundManager(sounds1), player(sounds1, PlayerTrail, BulletTrail, BulletExplode),
		enemy(EnemySpawn, EnemyTrail), bg(bg1), MenuMusic(music1)
	{

	}
	~App()
	{

	}
	void Start();
	bool Pause();
	void CheckHitBoxes();
	void Update();
};

