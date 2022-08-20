#pragma once
#include "const.h"
#include "inc/Camera.h"
#include "inc/PerlinNoise.h"
#include "inc/Time.h"
class BG : public Drawable
{
	VertexArray arr;
	VertexBuffer buffer;
	vector<float> perlin;
	Music& music;

	float musicBefore = 0;
	float offset;
	float getPerlinValue(Vector2i pos);
public:
	int onPulse;
	bool DoNotUpdate;
	BG(Music& music1)
		:music(music1)
	{

	}
	void Start(Camera& camera);
	bool Update();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

