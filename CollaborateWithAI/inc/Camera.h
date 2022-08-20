#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
//v.1.1
class Camera
{
private:
	
public:
	View camera;
public:
	Vector2f destination;
	Vector2f movePerFrame;
	Vector2f savePos;
	float Smoothness;
	float shake_lenght;
	float shake_intensity;
	bool shake_fade = false;
	float shake_startLength;
	int zoom_lenght;
	bool move = 0;
	bool shake = 0;
	bool lock = 0;
	bool Zoom = 0;
	bool shake1 = 0;
	float zoom_zoom;
	float scaling;
	FloatRect viewPort;
	
	void setStatic(Vector2f objectPos) { lock = 1; destination = objectPos; }
	void setDestination(Vector2f offset, int frameSmoothness)
	{
		move = 1;
		destination = offset;
		Smoothness = frameSmoothness;
		movePerFrame.x = (destination.x - camera.getCenter().x) / Smoothness;
		movePerFrame.y = (destination.y - camera.getCenter().y) / Smoothness;
	}
	void setAspectRatio(float ratio, Vector2f windowSize, Vector2i defaultSize)
	{
		if ((float)windowSize.x / windowSize.y < ratio)
		{
			camera.reset(FloatRect(0, 0, windowSize.x, int(windowSize.x / (ratio))));
			viewPort.left = 0;
			viewPort.top = 1.0 / windowSize.y * ((windowSize.y - int(windowSize.x / (ratio))) / 2);
			viewPort.width = 1;
			viewPort.height = ((float)windowSize.x / windowSize.y) / (ratio);
			scaling = (float)camera.getSize().y / defaultSize.y;
		}
		else if ((float)windowSize.x / windowSize.y > ratio)
		{
			camera.reset(FloatRect(0, 0, int(windowSize.y / (1 / ratio)), windowSize.y));
			viewPort.left = 1.0 / windowSize.x * ((windowSize.x - int(windowSize.y / (1 / ratio))) / 2);
			viewPort.top = 0;
			viewPort.width = (ratio) / ((float)windowSize.x / windowSize.y);
			viewPort.height = 1;
			scaling = (float)camera.getSize().x / defaultSize.x;
		}
		else
		{
			camera.reset(FloatRect(0, 0, windowSize.x, windowSize.y));
			viewPort.left = 0;
			viewPort.top = 0;
			viewPort.width = 1;
			viewPort.height = 1;
			scaling = (float)camera.getSize().x / defaultSize.x;
		}
	
		camera.setViewport(viewPort);
	}
	void setScaledAspectRatio(float ratio, Vector2f windowSize, Vector2i defaultSize)
	{
		if ((float)windowSize.x / windowSize.y < ratio)
		{
			camera.reset(FloatRect(0, 0, defaultSize.x, int(defaultSize.x / (ratio))));
			viewPort.left = 0;
			viewPort.top = 1.0 / windowSize.y * ((windowSize.y - int(windowSize.x / (ratio))) / 2);
			viewPort.width = 1;
			viewPort.height = ((float)windowSize.x / windowSize.y) / (ratio);
			scaling = (float)windowSize.y / defaultSize.y;
		}
		else if ((float)windowSize.x / windowSize.y > ratio)
		{
			camera.reset(FloatRect(0, 0, int(defaultSize.y / (1 / ratio)), defaultSize.y));
			viewPort.left = 1.0 / windowSize.x * ((windowSize.x - int(windowSize.y / (1 / ratio))) / 2);
			viewPort.top = 0;
			viewPort.width = (ratio) / ((float)windowSize.x / windowSize.y);
			viewPort.height = 1;
			scaling = (float)windowSize.x / defaultSize.x;
		}
		else
		{
			camera.reset(FloatRect(0, 0, defaultSize.x, defaultSize.y));
			viewPort.left = 0;
			viewPort.top = 0;
			viewPort.width = 1;
			viewPort.height = 1;
			scaling = (float)windowSize.x / defaultSize.x;
		}

		camera.setViewport(viewPort);
	}
	float getScale()
	{
		return scaling;
	}
	Vector2f getSize()
	{
		return camera.getSize();
	}

	void setShake(int intensity, float lenght, bool fadeShake)
	{
		if (shake_lenght > 0)
			camera.setCenter(savePos);
		savePos = camera.getCenter();
		shake = 1;
		shake_fade = fadeShake;
		shake_lenght = lenght;
		shake_startLength = lenght;
		shake_intensity = intensity * 10;
		camera.move(cos(rand() % 360) * 0.0174533 * shake_intensity, sin(rand() % 360) * 0.0174533 * shake_intensity);
	}
	void setZoomLevel(float zoom, int lenght)
	{
		Zoom = 1;
		zoom_zoom = zoom;
		zoom_lenght = lenght;
	}
	void Update(RenderWindow &window, float deltaSec)
	{
		if (camera.getCenter() != destination && move == 1 && Smoothness > 0)
		{
			camera.move(movePerFrame);
			window.setView(camera);
			Smoothness -= deltaSec;
			if (Smoothness == 0)
				move = 0;
		}
		if (shake_lenght > 0 && shake == 1)
		{
			shake1 = !shake1;
			if (shake1)
				camera.setCenter(savePos);
			else
			{

				if (!shake_fade)
					camera.move(cos(rand() % 360) * 0.0174533 * shake_intensity, sin(rand() % 360) * 0.0174533 * shake_intensity);
				else
					camera.move(cos(rand() % 360) * 0.0174533 * shake_intensity * ((float)shake_lenght / shake_startLength), sin(rand() % 360) * 0.0174533 * shake_intensity * ((float)shake_lenght / shake_startLength));
			}
			shake_lenght -= deltaSec;
			if (shake_lenght <= 0)
			{
				shake = 0;
				camera.setCenter(savePos);
			}
			window.setView(camera);
		}
		if (lock)
		{
			camera.setCenter(destination);
			window.setView(camera);
			lock = 0;
		}
		if (Zoom)
		{
			camera.zoom(zoom_zoom);
			zoom_lenght -= deltaSec;
			if (zoom_lenght <= 0)
				Zoom = 0;
			window.setView(camera);
		}
	}
};