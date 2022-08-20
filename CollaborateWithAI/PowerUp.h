#pragma once
#include "const.h"
#include "inc/Time.h"
#include "inc/TextureManager.h"
class PowerUp : public Drawable
{
	friend class App;
	float cntDown;
	RectangleShape powerUp;
	bool active;
	int ID;
public:
	void Start(TextureManager& texture);
	void Update(View& cameraView);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

