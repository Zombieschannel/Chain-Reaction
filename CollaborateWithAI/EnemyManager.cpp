#include "EnemyManager.h"

void EnemyManager::Start(TextureManager* textureManager, const Vector2f* playerPos)
{
	enemies.resize(c_maxEnemies);
	for (int i = 0; i < c_maxEnemies; i++)
	{
		enemies[i].Setup(textureManager);
		enemies[i].playerLocation = playerPos;
	}
	SpawnTime = c_SpawnStartSec;
	SpawnStart = c_SpawnStartSec;
	speedMultiplier = 1;
}

void EnemyManager::Spawn(View& cameraView)
{
	if (toSpawn.x == -1 && toSpawn.y == -1)
	{
		toSpawn = Vector2f(rand() % (int)cameraView.getSize().x,
			rand() % (int)cameraView.getSize().y);
	}
	SpawnTime -= TimeManager::getDeltaTime().asSeconds();
	if (SpawnTime <= 0)
	{
		if (SpawnStart > c_SpawnStartMin)
			SpawnStart /= 1.01;
		SpawnTime = SpawnStart;
		speedMultiplier *= 1.0003;
		for (int i = 0; i < c_maxEnemies; i++)
		{
			if (!enemies[i].active)
			{
				enemies[i].active = 1;
				enemies[i].hp = c_enemyHP;
				enemies[i].player.setPosition(toSpawn);
				while (1)
				{
					Vector2f randPos = Vector2f(rand() % (int)cameraView.getSize().x,
						rand() % (int)cameraView.getSize().y);
					if (Distance::Point_Point(randPos, *enemies[i].playerLocation) > c_MinSpawnDistance)
					{
						toSpawn = randPos;
						break;
					}
				}
				break;
			}
		}
	}
	else if (SpawnTime <= 1)
	{
		enemySpawn.setPosition(toSpawn);
		enemySpawn.createNew();
	}
}

void EnemyManager::Update(RenderWindow& window, View& cameraView)
{
	Spawn(cameraView);
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].Update(window, cameraView, speedMultiplier);
		if (enemies[i].active)
		{
			enemyTrail.setPosition(enemies[i].player.getPosition());
			enemyTrail.createNew();
		}
	}
}

int EnemyManager::FindClosestEnemy(Vector2f pos, float& distance)
{
	unsigned int ID = -1;
	float shortest = INT32_MAX;
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!enemies[i].active)
			continue;
		float dist = Distance::Point_Point(enemies[i].player.getPosition(), pos);
		if (dist < shortest)
		{
			shortest = dist;
			ID = i;
		}
	}
	distance = shortest;
	return ID;
}

void EnemyManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].active)
			target.draw(enemies[i]);
	}
}
