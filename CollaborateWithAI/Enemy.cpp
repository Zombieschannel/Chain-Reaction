#include "Enemy.h"

void Enemy::Start()
{
	player.setFillColor(enemyColor);
	hp = c_enemyHP;
	active = 0;
	wanderMode = 0;
}

void Enemy::SetWanderLocation(View& cameraView)
{
	wanderMode = 1;
	wanderLocation = Vector2f(rand() % (int)cameraView.getSize().x, rand() % (int)cameraView.getSize().y);
}

void Enemy::Update(RenderWindow& window, View& cameraView, float speedMultiplier)
{
	if (wanderMode)
	{
		if (Distance::Point_Point(player.getPosition(), wanderLocation) < 20)
		{
			SetWanderLocation(cameraView);
		}
	}

	float rot;
	Vector2f dir = (wanderMode ? wanderLocation : (*playerLocation)) - player.getPosition();
	rot = atan2(dir.y, dir.x) * 57.2958;
	player.setRotation(rot + 90);

	Vector2f move;
	move = Vector2f(cos(rot * 0.0174533) * c_enemySpeed * TimeManager::getDeltaTime().asSeconds(),
		sin(rot * 0.0174533) * c_enemySpeed * TimeManager::getDeltaTime().asSeconds());
	player.move(move.x * speedMultiplier, move.y * speedMultiplier);
}

void Enemy::Delete()
{
	active = 0;
}
