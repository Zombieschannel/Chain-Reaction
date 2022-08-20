#pragma once
//1.2
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;
class ParticleSystem : public Drawable
{
public:
	int MaxParticles = 100;
	bool fade = false;
private:
	int cound = 0;
	int Summon = 0;
	float r1, g1, b1;

	bool moveP = false;
	bool changeColor = false;
	bool randCol = false;

	bool reverse = false;
	int reverseSteps = 0;
	int StartSpeed = 10;
	int EndSpeed = 10;
	int lifeTime = 1;
	int points = 1;
	int rotate = 0;
	int particlesPS = 1;
	int spawnDelay = 0;
	int gravityS = 0;
	int extraDX = 0;
	int extraDY = 0;
	Vector2f scale;
	Texture* partT;
	Vector2f particlePosition = Vector2f(0, 0);
	Vector2f RecSize = Vector2f(200, 200);
	Color startColor = Color::White;
	Color endColor = Color::White;
	int startSize = 1;
	int endSize = 1;
	int speedChange = 0;
public:
	bool randomRotation = false;
	vector<float> lifeLeft;
	vector<bool> inUse;
	vector<Vector2f> pos;
	vector<CircleShape> particle;
	Color randColors[8] = { Color::White, Color::Yellow, Color(255, 128, 0), Color::Red, Color::Magenta, Color::Cyan, Color::Blue, Color::Green };
	void setSpawnOffset(int x, int y) { extraDX = x; extraDY = y; }
	void setSpawnSize(int x, int y) { RecSize.x = x; RecSize.y = y; }
	void setFillColor(Color start, Color end) { startColor = start; endColor = end; r1 = (float)(endColor.r - startColor.r) / lifeTime; g1 = (float)(endColor.g - startColor.g) / lifeTime; b1 = (float)(endColor.b - startColor.b) / lifeTime; }
	void SetSize(int start, int end) { startSize = start; endSize = end; }
	void setGravity(float scale) { gravityS = scale; }
	void setSpawnDelay(int delay) { spawnDelay = delay; }
	void SetPoints(int number) { points = number; }
	void setRotation(int rotation) { rotate = rotation; }
	void SetRotation(int rotation)
	{
		for (int i = 0; i < MaxParticles; i++)
			if (inUse[i])
				particle[i].setRotation(rotation);
	}
	void setSpawnPerCall(int number) { particlesPS = number; }
	void setLifeTime(int number) { lifeTime = number; r1 = (float)(endColor.r - startColor.r) / lifeTime; g1 = (float)(endColor.g - startColor.g) / lifeTime; b1 = (float)(endColor.b - startColor.b) / lifeTime; }
	void setSlowness(int start, int end) { StartSpeed = start; EndSpeed = end; }
	void setPosition(Vector2f position) { particlePosition = position; }
	void setReverseSteps(int steps) { reverseSteps = steps; }
	void setTexture(Texture& texture)
	{
		partT = &texture;
		for (int a = 0; a < MaxParticles; a++)
			particle[a].setTexture(partT);
	}
	void enableTextures(bool texture)
	{
		for (int a = 0; a < MaxParticles; a++)
		{
			if (texture == 1)
				particle[a].setTexture(partT);
			else
				particle[a].setTexture(NULL);
		}
	}
	Color getStartFillColor() { return startColor; }
	Color getEndFillColor() { return endColor; }
	Vector2f getSpawnOffset() { Vector2f a1; a1.x = extraDX; a1.y = extraDY; return a1; }
	Vector2f getSpawnSize() { Vector2f a1; a1.x = RecSize.x; a1.y = RecSize.y; return a1; }
	int getStartSize() { return startSize; }
	int getEndSize() { return endSize; }
	int getGravity() { return gravityS; }
	int getSpawnDelay() { return spawnDelay; }
	int getPoints() { return points; }
	int getRotation() { return rotate; }
	int getLifeTime() { return lifeTime; }
	int getStartSlowness() { return StartSpeed; }
	int getEndSlowness() { return EndSpeed; }
	int getSpawnPerCall() { return particlesPS; }
	Vector2f getPosition() { return particlePosition; }
	int getReverseSteps() { return reverseSteps; }
	bool getFade() { return fade; }
	bool getMoving() { return moveP; }
	bool getChangeColor() { return changeColor; }
	bool getReverse() { return reverse; }
	bool getRandomRotaion() { return randomRotation; }
	void move(int x, int y) { particlePosition.x += x; particlePosition.x += y; }
	/*void setScale(float x, float y)
	{
		this->scale.x = x;
		this->scale.y = y;
		for (int i = 0; i < MaxParticles; i++)
			particle[i].setScale(this->scale);
	}*/
	Vector2f getScale() { return this->scale; }
	void loadSettings(String directory)
	{
		Image l;
		if (l.loadFromFile(directory))
		{
			Color c = l.getPixel(0, 0);
			fade = c.r;
			randomRotation = c.g;
			moveP = c.b;
			changeColor = c.a;
			c = l.getPixel(1, 0);
			randCol = c.r;
			reverse = c.g;
			reverseSteps = c.b;
			StartSpeed = c.a;
			c = l.getPixel(2, 0);
			lifeTime = c.r;
			points = c.g;
			rotate = c.b;
			particlesPS = c.a;
			c = l.getPixel(3, 0);
			spawnDelay = c.r;
			gravityS = c.g;
			extraDX = c.b;
			extraDY = c.a;
			c = l.getPixel(4, 0);
			RecSize.x = c.r;
			RecSize.y = c.g;
			startSize = c.b;
			endSize = c.a;
			c = l.getPixel(5, 0);
			startColor = c;
			c = l.getPixel(6, 0);
			endColor = c;
			c = l.getPixel(7, 0);
			EndSpeed = c.r;
		}
	}
	void reset()
	{
		particle.clear();
		pos.clear();
		inUse.clear();
		lifeLeft.clear();
		for (int a = 0; a < MaxParticles; a++)
		{
			CircleShape ab;
			particle.push_back(ab);
			int ac = 0;
			lifeLeft.push_back(ac);
			bool aa = 0;
			inUse.push_back(aa);
			Vector2f bb;
			pos.push_back(bb);
		}
	}
	void createAll(bool ChangeColor, bool MoveParticles, bool RandomRotation, bool Fade, int LifeTime, bool Reverse)
	{
		reverse = Reverse;
		r1 = (float)(endColor.r - startColor.r) / lifeTime;
		g1 = (float)(endColor.g - startColor.g) / lifeTime;
		b1 = (float)(endColor.b - startColor.b) / lifeTime;
		lifeTime = LifeTime;
		changeColor = ChangeColor;
		if (ChangeColor == 0)
			randCol = true;
		else
			randCol = false;
		moveP = MoveParticles;
		randomRotation = RandomRotation;
		fade = Fade;
		particlePosition.x = 0;
		particlePosition.y = 0;
		speedChange = (EndSpeed - StartSpeed) / lifeTime;
	}
	void createNew()
	{
		if (cound >= spawnDelay)
		{
			cound = 0;
			for (int a = 0; a < MaxParticles; a++)
			{
				if (inUse[a] == false)
				{
					particle[a].setRadius(startSize);
					if (randomRotation == true)
						particle[a].setRotation(rand() % 360);
					else
						particle[a].setRotation(0);
					if (randCol == true)
						particle[a].setFillColor(randColors[rand() % 8]);
					else
						particle[a].setFillColor(Color(startColor.r, startColor.g, startColor.b));
					particle[a].setOrigin(particle[a].getRadius(), particle[a].getRadius());
					particle[a].setPointCount(points);
					particle[a].setPosition(particlePosition);
					inUse[a] = 1;
					pos[a].x = (rand() % (int)RecSize.x - (int)RecSize.x / 2 + extraDX);
					pos[a].y = (rand() % (int)RecSize.y - (int)RecSize.y / 2 + extraDY);
					lifeLeft[a] = lifeTime;
					if (reverse == true)
					{
						for (int b = 0; b < reverseSteps; b++)
							particle[a].move(pos[a]);
						pos[a].x = -pos[a].x;
						pos[a].y = -pos[a].y;
					}

					Summon++;
					if (Summon >= particlesPS)
					{
						Summon = 0;
						break;
					}
				}
			}
		}
		cound++;
	}
	void update(float deltaSec)
	{
		for (int a = 0; a < MaxParticles; a++)
		{
			if (lifeLeft[a] <= 0)
			{
				inUse[a] = 0;
			}
			if (inUse[a] == 1)
			{
				if (moveP == true)
					particle[a].move((pos[a].x / (StartSpeed + (((float)(EndSpeed - StartSpeed) / lifeTime) * (lifeTime - lifeLeft[a])))) * deltaSec, (pos[a].y / (StartSpeed + (((float)(EndSpeed - StartSpeed) / lifeTime) * (lifeTime - lifeLeft[a])))) * deltaSec);
				particle[a].setRadius(particle[a].getRadius() + (float)(endSize - startSize) / lifeTime);
				particle[a].rotate(rotate * deltaSec);

				pos[a].y += gravityS * 0.1;
				if (changeColor == true)
				{
					particle[a].setFillColor(Color(particle[a].getFillColor().r + (float)r1, particle[a].getFillColor().g + (float)g1, particle[a].getFillColor().b + (float)b1));
				}
				if (fade == true)
					particle[a].setFillColor(Color(particle[a].getFillColor().r, particle[a].getFillColor().g, particle[a].getFillColor().b, (float)((255 / lifeTime) * lifeLeft[a])));
				particle[a].setOrigin(particle[a].getRadius(), particle[a].getRadius());
				lifeLeft[a] -= deltaSec;
			}
		}
	}
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (int i = 0; i < MaxParticles; i++)
			if (inUse[i])
			{
				target.draw(particle[i], states);
			}
	}
};