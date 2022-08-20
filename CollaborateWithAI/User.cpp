#include "User.h"

void User::Setup(TextureManager* textureManager)
{
	this->textureManager = textureManager;
	player.setTexture(&(*textureManager)["player"]);
	player.setSize((Vector2f)c_playerSize);
	player.setOrigin(player.getSize().x / 2, player.getSize().y / 10 * 6);
	active = 1;

	Start();
}

void User::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(player, states);
}

