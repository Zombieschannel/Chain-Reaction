#include "Bullet.h"

void Bullet::Start(TextureManager& textures)
{
	active = 0;
	bullet.setRadius(c_playerBulletSize);
	bullet.setOrigin(c_playerBulletSize, c_playerBulletSize);
	bullet.setFillColor(BulletColor);
	beam.setSize(Vector2f(c_playerSize.x / 2, 0));
	beam.setOrigin(beam.getSize().x / 2, 0);
	beam.setFillColor(Color(BulletColor.r, BulletColor.g, BulletColor.b, 64));
	beam.setTexture(&textures["beam"]);
	beam.setTextureRect(IntRect(0, 0, 49, 1));
}

void Bullet::Delete()
{
	active = 0;
}

void Bullet::Spawn(Vector2f additionalDir, Vector2f location, float angle)
{
	bullet.setPosition(location);
	active = 1;
	additionalDir.x /= 2;
	additionalDir.y /= 2;
	bullet.setRotation(angle);
	lifeTime = c_playerBulletLifeTime;
	this->targetLocation = targetLocation;
	this->additionalDir = additionalDir;
	hitCnt = 0;
	speed = c_playerBulletSpeed;
	doNotDrawBeam = 0;
}

void Bullet::Bounce(float angle, const Vector2f* targetPos)
{
	bullet.setRotation(angle);
	hitCnt++;
	lifeTime += 0.1;
	speed *= 1.05;
	this->targetPos = targetPos;
}

void Bullet::Update(ParticleSystem& bulletExplode)
{
	if (!active)
		return;
	if (targetPos != nullptr && hitCnt > 0)
	{
		Vector2f target = (*targetPos) - bullet.getPosition();
		float beamRot = atan2(target.y, target.x) * 57.2958 - 90;
		beam.setRotation(beamRot);
		beam.setPosition(bullet.getPosition());
		beam.setSize(Vector2f(beam.getSize().x, Distance::Point_Point(*targetPos, bullet.getPosition())));
	}

	Vector2f dirN = Vector2f(cos(bullet.getRotation() * 0.0174533) * speed, sin(bullet.getRotation() * 0.0174533) * speed);
	bullet.move((dirN + additionalDir) * TimeManager::getDeltaTime().asSeconds());
	lifeTime -= TimeManager::getDeltaTime().asSeconds();
	if (lifeTime <= 0)
	{
		bulletExplode.setPosition(bullet.getPosition());
		bulletExplode.createNew();
		active = 0;
	}
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (active)
	{

		target.draw(bullet, states);
	}
}
