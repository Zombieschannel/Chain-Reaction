#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "inc/ParticleSystem.h"
#include "inc/SoundManager.h"
using namespace sf;
using namespace std;

//constants
static const Color enemyColor = Color(255, 0, 0, 255);
static const Color playerColor = Color(0, 128, 255, 255);
static const Color AIColor = Color(0, 255, 32, 255);
static const Color BulletColor = Color(0, 192, 255, 255);

static const Vector2u c_playerSize = Vector2u(20, 25);
static const float c_playerMaxAcc = 1.4;
static const float c_playerMinAcc = 0.1;
static const float c_playerAcc = 10;
static const int c_enemySpeed = 75;

static const int c_playerHP = 5;
static const int c_enemyHP = 1;

static const float c_userHitBoxSize = 8;
static const float c_enemyHitBoxSize = 10;

static const float c_maxAsteroids = 5;
static const int c_SpawnAsteroidSec = 10;
static const int c_SpawnAsteroidMinDist = 800;

static const int c_maxEnemies = 300;

static const float c_SpawnStartSec = 2.5;
static const float c_SpawnStartMin = 0.1;

static const int c_MinSpawnDistance = 200;

static const float c_AsteroidsRadius[3] = {75, 100, 125};
static const float c_AsteroidsSpeed[3] = {60, 50, 40};

static const int c_playerBulletRecharge = 5; //sec
static const int c_playerBulletSize = 6;
static const int c_playerBulletSpeed = 300;
static const int c_playerBulletLifeTime = 3; // sec
static const int c_playerMaxBullets = 10;
static const int c_playerStartBullets = 3;

static const int c_powerUpSpawnRate = 10;
static const Vector2u c_powerUpSize = Vector2u(50, 50);

static const string AppName = "Chain reaction";

static const Vector2u BGTiles = Vector2u(16, 9);

static const vector<float> BGswitchPoints =
{
	24.2, 47.1, 58.3, 80.6, 91.3, 133.9, 154.7, 174.7, 232.8, 252.4, 314.5, 353.9, 392.5, 431.3, 9999.9
};
static const vector<unsigned int> BGswitchIndices =
{
	0, 2,		1,	4,		2,	5,		3,		0,	   1,	2,		6,		3,	 4,		  5,	0
};
static const vector<Color>BGSwitchColors =
{
	Color(25, 25, 255),//dark blue 0
	Color(255, 25, 25),//red 1
	Color(25, 255, 25),//green 2
	Color(25, 255, 255),//cyan 3
	Color(255, 25, 255),//magenta 4
	Color(150, 150, 150),//grey 5 
	Color(100, 100, 100),//dark grey 6
};