#include "Player.h"

void Player::Start()
{
	player.setFillColor(playerColor);
	hp = c_playerHP;
	acc = Vector2f(0, 0);
	
	for (int i = 0; i < c_playerMaxBullets; i++)
	{
		bullet[i].bulletRecharge = 0;
		bullet[i].Start(*textureManager);
	}
	usingBullets = c_playerStartBullets;
	playerMaxSpeed = 1;
}

void Player::Update(RenderWindow& window, View& cameraView)
{
	Vector2f dirAcc = Vector2f(cos((player.getRotation() - 90) * 0.0174533), sin((player.getRotation() - 90) * 0.0174533));
	if (InputEvent::isKeyPressed(Keyboard::W) || InputEvent::isKeyPressed(Keyboard::Up))
	{
		acc.x += dirAcc.x * c_playerAcc * TimeManager::getDeltaTime().asSeconds();
		acc.y += dirAcc.y * c_playerAcc * TimeManager::getDeltaTime().asSeconds();
		playerTrail.setPosition(player.getPosition());
		playerTrail.createNew();
	}
	if (InputEvent::isKeyPressed(Keyboard::S) || InputEvent::isKeyPressed(Keyboard::Down))
	{
		acc.x -= dirAcc.x * c_playerAcc * TimeManager::getDeltaTime().asSeconds();
		acc.y -= dirAcc.y * c_playerAcc * TimeManager::getDeltaTime().asSeconds();
		playerTrail.setPosition(player.getPosition());
		playerTrail.createNew();
	}
	acc.x -= (acc.x * 6) * TimeManager::getDeltaTime().asSeconds();
	acc.y -= (acc.y * 6) * TimeManager::getDeltaTime().asSeconds();
	if (abs(acc.x) > c_playerMaxAcc)
		acc.x = c_playerMaxAcc * (acc.x / abs(acc.x));
	if (abs(acc.y) > c_playerMaxAcc)
		acc.y = c_playerMaxAcc * (acc.y / abs(acc.y));

	/*if (abs(acc.x) < c_playerMinAcc)
		acc.x = 0;
	if (abs(acc.y) < c_playerMinAcc)
		acc.y = 0;*/
	player.move(144 * acc.x * playerMaxSpeed * TimeManager::getDeltaTime().asSeconds(), 144 * acc.y * playerMaxSpeed * TimeManager::getDeltaTime().asSeconds());
	if (player.getPosition().x < 0)
		player.setPosition(0, player.getPosition().y);
	if (player.getPosition().y < 0)
		player.setPosition(player.getPosition().x, 0);

	if (player.getPosition().x > cameraView.getSize().x)
		player.setPosition(cameraView.getSize().x, player.getPosition().y);
	if (player.getPosition().y > cameraView.getSize().y)
		player.setPosition(player.getPosition().x, cameraView.getSize().y);
	float rot; 
	Vector2f dir = (Vector2f)InputEvent::getMousePosition(window) - player.getPosition();
	rot = atan2(dir.y, dir.x) * 57.2958;
	player.setRotation(rot + 90);
	
	if (!InputEvent::isButtonPressed(Mouse::Left))
		mcHold = 0;

	for (int i = 0; i < usingBullets; i++)
	{
		bullet[i].bulletRecharge -= TimeManager::getDeltaTime().asSeconds();
		if (bullet[i].bulletRecharge <= 0 && !bullet[i].active)
		{
			if (InputEvent::isButtonPressed(Mouse::Left) && !mcHold)
			{
				sounds.reset("shoot");
				mcHold = 1;
				bullet[i].bulletRecharge = c_playerBulletRecharge;
				bullet[i].Spawn(acc, player.getPosition(), rot);
				break;
			}
		}
		bullet[i].Update(bulletExplode);
		if (bullet[i].active)
		{
			bulletTrail.setPosition(bullet[i].bullet.getPosition());
			bulletTrail.createNew();
		}

	}
}
