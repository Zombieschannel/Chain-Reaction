#include "Asteroid.h"

void Asteroids::Start(TextureManager& textures)
{
	asteroids.resize(c_maxAsteroids);
	for (int i = 0; i < c_maxAsteroids; i++)
	{
		asteroids[i].shape.setPointCount(50);
		asteroids[i].shape.setTexture(&textures["asteroid"]);
		asteroids[i].shadow.setPointCount(50);
		asteroids[i].shadow.setTexture(&textures["asteroidShadow"]);
		asteroids[i].shadow.setOutlineThickness(-6);
		asteroids[i].shadow.setOutlineColor(Color(255, 255, 255, 32));
		asteroids[i].active = 0;
	}
	asteroidSpawnRate = c_SpawnAsteroidSec;
}

void Asteroids::Update(View& cameraView)
{
	asteroidSpawnRate -= TimeManager::getDeltaTime().asSeconds();
	if (asteroidSpawnRate <= 0)
	{
		asteroidSpawnRate = c_SpawnAsteroidSec;
		for (int i = 0; i < c_maxAsteroids; i++)
		{
			if (!asteroids[i].active)
			{
				asteroids[i].active = 1;
				int randomAsset = rand() % 3;
				asteroids[i].shape.setRadius(c_AsteroidsRadius[randomAsset] - 2);
				asteroids[i].shadow.setRadius(c_AsteroidsRadius[randomAsset]);
				asteroids[i].rotateSpeed = rand() % 20 + 15;
				asteroids[i].shape.setOrigin(asteroids[i].shape.getRadius(), asteroids[i].shape.getRadius());
				asteroids[i].shadow.setOrigin(asteroids[i].shadow.getRadius(), asteroids[i].shadow.getRadius());
				asteroids[i].id = randomAsset;


				int wall = rand() % 2; //0 vertical 1 horizontal
				if (wall)
				{
					int wall2 = rand() % 2;//0 left 1 right
					int randPos = rand() % (int)cameraView.getSize().y;
					if (wall2)
						asteroids[i].shape.setPosition(cameraView.getSize().x + asteroids[i].shape.getRadius(), randPos);
					else
						asteroids[i].shape.setPosition(-asteroids[i].shape.getRadius(), randPos);
					int a = 100;
					while (a--)
					{
						int wall3 = rand() % 2;
						int randPos2 = rand() % (int)cameraView.getSize().x;
						if (wall3)
							asteroids[i].targetPos = Vector2f(randPos2, cameraView.getSize().y + asteroids[i].shape.getRadius());
						else
							asteroids[i].targetPos = Vector2f(randPos2, -asteroids[i].shape.getRadius());
						if (Distance::Point_Point(asteroids[i].targetPos, asteroids[i].shape.getPosition()) > c_SpawnAsteroidMinDist)
						{
							//bool allowed = 1;
							//for (int j = 0; j < c_maxAsteroids; j++)
							//	if (Collision::)
							//if (allowed)
							break;
						}
					}
					if (!a)
						asteroids[i].active = 0;
				}
				else
				{
					int wall2 = rand() % 2;//0 top 1 bottom
					int randPos = rand() % (int)cameraView.getSize().x;
					if (wall2)
						asteroids[i].shape.setPosition(randPos, cameraView.getSize().y + asteroids[i].shape.getRadius());
					else
						asteroids[i].shape.setPosition(randPos, -asteroids[i].shape.getRadius());
					int a = 100;
					while (a--)
					{
						int wall3 = rand() % 2;
						int randPos2 = rand() % (int)cameraView.getSize().y;
						if (wall3)
							asteroids[i].targetPos = Vector2f(cameraView.getSize().x + asteroids[i].shape.getRadius(), randPos2);
						else
							asteroids[i].targetPos = Vector2f(-asteroids[i].shape.getRadius(), randPos2);
						if (Distance::Point_Point(asteroids[i].targetPos, asteroids[i].shape.getPosition()) > c_SpawnAsteroidMinDist)
						{
							break;
						}
					}
					if (!a)
						asteroids[i].active = 0;
				}
				break;
			}
		}
	}

	//update asteroids
	for (int i = 0; i < asteroids.size(); i++)
	{
		Vector2f dir = asteroids[i].targetPos - asteroids[i].shape.getPosition();
		float rot = atan2(dir.y, dir.x) * 57.2958;
		Vector2f move = Vector2f(cos(rot * 0.0174533) * c_AsteroidsSpeed[asteroids[i].id], sin(rot * 0.0174533) * c_AsteroidsSpeed[asteroids[i].id]);
		move.x *= TimeManager::getDeltaTime().asSeconds();
		move.y *= TimeManager::getDeltaTime().asSeconds();
		asteroids[i].shape.move(move);
		asteroids[i].shadow.setPosition(asteroids[i].shape.getPosition());
		asteroids[i].shape.rotate(asteroids[i].rotateSpeed * TimeManager::getDeltaTime().asSeconds());
		if (asteroids[i].shape.getPosition().x + asteroids[i].shape.getRadius() < 0 || asteroids[i].shape.getPosition().x > cameraView.getSize().x + asteroids[i].shape.getRadius() ||
			asteroids[i].shape.getPosition().y + asteroids[i].shape.getRadius() < 0 || asteroids[i].shape.getPosition().y > cameraView.getSize().y + asteroids[i].shape.getRadius())
		{
			if (Distance::Point_Point(asteroids[i].shape.getPosition(), asteroids[i].targetPos) < c_SpawnAsteroidMinDist)
			{
				asteroids[i].active = 0;
			}
		}
	}

}

void Asteroids::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < asteroids.size(); i++)
		if (asteroids[i].active)
		{
			target.draw(asteroids[i].shape, states);
			target.draw(asteroids[i].shadow, states);
		}
}
