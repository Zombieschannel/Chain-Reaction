#pragma once
#include "Enemy.h"
#include "inc/Collisions.h"
class EnemyManager : public Drawable
{
	friend class App;
	double SpawnStart;
	double SpawnTime;
	double speedMultiplier;
	vector<Enemy> enemies;
	ParticleSystem& enemySpawn;
	ParticleSystem& enemyTrail;
	Vector2f toSpawn = Vector2f(-1, -1);
public:
	EnemyManager(ParticleSystem& enemySpawn1, ParticleSystem& enemyTrail1)
		:enemySpawn(enemySpawn1), enemyTrail(enemyTrail1)
	{

	}
	~EnemyManager()
	{

	}
	void Start(TextureManager* textureManager, const Vector2f* playerPos);
	
	void Spawn(View& cameraView);

	void Update(RenderWindow& window, View& cameraView);

	int FindClosestEnemy(Vector2f pos, float& distance);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

