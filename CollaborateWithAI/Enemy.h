#pragma once
#include "User.h"
#include "inc/InputEvent.h"
#include "inc/Time.h"
#include "inc/Collisions.h"
class Enemy : public User
{
	virtual void Start();
public:
	const Vector2f* playerLocation;
	Vector2f wanderLocation;
	bool wanderMode;
	void SetWanderLocation(View& cameraView);
	void Update(RenderWindow& window, View& cameraView, float speedMultiplier);
	void Delete();
	~Enemy()
	{

	}
};

