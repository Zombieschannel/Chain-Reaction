#include "PowerUp.h"

void PowerUp::Start(TextureManager& texture)
{
	cntDown = c_powerUpSpawnRate;
	powerUp.setSize((Vector2f)c_powerUpSize);
	powerUp.setOrigin(c_powerUpSize.x / 2.0, c_powerUpSize.y / 2.0);
	powerUp.setTexture(&texture["power"]);
	powerUp.setOutlineThickness(4);
	active = 0;
}

void PowerUp::Update(View& cameraView)
{
	if (!active)
	{
		cntDown -= TimeManager::getDeltaTime().asSeconds();
		if (cntDown <= 0)
		{
			cntDown = c_powerUpSpawnRate;
			active = 1;
			ID = rand() % 3;
			powerUp.setTextureRect(IntRect(100 * ID, 0, 100, 100));
			Vector2i Xaxis = Vector2i(cameraView.getSize().x / 10 * 1, cameraView.getSize().x / 10 * 9);
			Vector2i Yaxis = Vector2i(cameraView.getSize().y / 10 * 1, cameraView.getSize().y / 10 * 9);
			Vector2i randPos = Vector2i(rand() % (Xaxis.y - Xaxis.x) + Xaxis.x, rand() % (Yaxis.y - Yaxis.x) + Yaxis.x);
			powerUp.setPosition((Vector2f)randPos);
		}
	}
}

void PowerUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (active)
		target.draw(powerUp, states);
}
