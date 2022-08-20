#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
class InputEvent
{
	vector<bool> keys;
	vector<bool> keysR;
	vector<bool> mouse;
	vector<bool> mouseR;
	vector<vector<bool>> joyStickButton;
	vector<vector<float>> joystickAxis;
	vector<int> lastJoystickPressed;
	int scroll = 0;
	bool hasFocus = 1;
	Vector2i lastMcPos;
	Vector2i lastRelativeMcPos;
	char textEntered;
	InputEvent() {};
public:
	InputEvent(const InputEvent&) = delete;
	static InputEvent& Get()
	{
		static InputEvent instance;
		return instance;
	}
	static void Start(Window& relativeTo)
	{
		Get().IStart(relativeTo);
	}
	static void OnceUpdate()
	{
		Get().IOnceUpdate();
	}
	static void EventUpdate(Event& event)
	{
		Get().IEventUpdate(event);
	}
	static bool isKeyPressed(Keyboard::Key key)
	{
		return Get().IisKeyPressed(key);
	}
	static bool isButtonPressed(Mouse::Button button)
	{
		return Get().IisButtonPressed(button);
	}
	static bool isKeyReleased(Keyboard::Key key)
	{
		return Get().IisKeyReleased(key);
	}
	static bool isButtonReleased(Mouse::Button button)
	{
		return Get().IisButtonReleased(button);
	}
	static void setMousePosition(Vector2i position)
	{
		Get().IsetMousePosition(position);
	}
	static void setMousePosition(Vector2i position, Window& relativeTo)
	{
		Get().IsetMousePosition(position, relativeTo);
	}
	static Vector2i getMousePosition()
	{
		return Get().IgetMousePosition();
	}
	static Vector2i getMousePosition(Window& relativeTo)
	{
		return Get().IgetMousePosition(relativeTo);
	}
	static bool isJoystickKeyPressed(int joystickID, unsigned int key)
	{
		return Get().IisJoystickKeyPressed(joystickID, key);
	}
	static float getAxisPosition(int joystickID, Joystick::Axis axis)
	{
		return Get().IgetAxisPosition(joystickID, axis);
	}
	static int getJoystickButtonPressed(int joystickID)
	{
		return Get().IgetJoystickButtonPressed(joystickID);
	}
	static int getScrollData()
	{
		return Get().IgetScrollData();
	}
	static bool WindowHasFocus()
	{
		return Get().IWindowHasFocus();
	}
	static char TextEntered()
	{
		return Get().IgetTextEntered();
	}
private:
	void IStart(Window& relativeTo)
	{
		keys.resize(Keyboard::KeyCount, 0);
		keysR.resize(Keyboard::KeyCount, 0);
		mouse.resize(Mouse::ButtonCount, 0);
		mouseR.resize(Mouse::ButtonCount, 0);
		lastMcPos = Vector2i(Mouse::getPosition());
		lastJoystickPressed.resize(Joystick::Count, -1);
		lastRelativeMcPos = Vector2i(Mouse::getPosition(relativeTo));
	}
	void IOnceUpdate()
	{
		for (int i = 0; i < Keyboard::KeyCount; i++)
			keysR[i] = 0;
		for (int i = 0; i < Mouse::ButtonCount; i++)
			mouseR[i] = 0;
		for (int i = 0; i < Joystick::Count; i++)
			lastJoystickPressed[i] = -1;
		scroll = 0;
		textEntered = '\0';
	}
	void IEventUpdate(Event& event)
	{
		if (event.type == Event::MouseWheelScrolled)
		{
			scroll = event.mouseWheelScroll.delta;
		}
		if (event.type == Event::GainedFocus)
		{
			hasFocus = 1;
		}
		if (event.type == Event::LostFocus)
		{
			hasFocus = 0;
			for (int i = 0; i < Keyboard::KeyCount; i++)
				keys[i] = 0;
			for (int i = 0; i < Mouse::ButtonCount; i++)
				mouse[i] = 0;
		}
		for (int i = 0; i < Keyboard::KeyCount; i++)
		{
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == (Keyboard::Key)i)
					keys[i] = 1;
			}
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == (Keyboard::Key)i)
				{
					keys[i] = 0;
					keysR[i] = 1;
				}
			}
		}
		for (int i = 0; i < Mouse::ButtonCount; i++)
		{
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == (Mouse::Button)i)
					mouse[i] = 1;
			}
			if (event.type == Event::MouseButtonReleased)
			{
				if (event.key.code == (Mouse::Button)i)
				{
					mouse[i] = 0;
					mouseR[i] = 1;
				}
			}

		}
		for (int i = 0; i < Joystick::Count; i++)
		{
			if (event.type == Event::JoystickButtonPressed && event.joystickButton.joystickId == i)
			{
				lastJoystickPressed[i] = event.joystickButton.button;
			}
		}
		if (event.type == Event::TextEntered)
		{
			textEntered = event.text.unicode;
		}
	}
	bool IisKeyPressed(Keyboard::Key key)
	{
		return keys[(int)key];
	}
	bool IisButtonPressed(Mouse::Button button)
	{
		return mouse[(int)button];
	}
	bool IisKeyReleased(Keyboard::Key key)
	{
		if (keysR[(int)key])
		{
			keysR[(int)key] = 0;
			return 1;
		}
		return 0;
	}
	bool IisButtonReleased(Mouse::Button button)
	{
		if (mouseR[(int)button])
		{
			mouseR[(int)button] = 0;
			return 1;
		}
		return 0;
	}
	bool IWindowHasFocus()
	{
		return hasFocus;
	}
	void IsetMousePosition(Vector2i position, Window& relativeTo)
	{
		if (hasFocus)
			Mouse::setPosition(position, relativeTo);
	}
	void IsetMousePosition(Vector2i position)
	{
		if (hasFocus)
			Mouse::setPosition(position);
	}
	bool IisJoystickKeyPressed(int joystickID, unsigned int key)
	{
		return Joystick::isButtonPressed(joystickID, key);
	}
	float IgetAxisPosition(int joystickID, Joystick::Axis axis)
	{
		return Joystick::getAxisPosition(joystickID, axis);
	}
	char IgetTextEntered()
	{
		return textEntered;
	}
	int IgetJoystickButtonPressed(int joystickID)
	{
		return lastJoystickPressed[joystickID];
	}
	int IgetScrollData()
	{
		return scroll;
	}
	Vector2i IgetMousePosition()
	{
		if (hasFocus)
		{
			lastMcPos = Mouse::getPosition();
			return Mouse::getPosition();
		}
		return lastMcPos;
	}
	Vector2i IgetMousePosition(Window& relativeTo)
	{
		if (hasFocus)
		{
			lastRelativeMcPos = Mouse::getPosition(relativeTo);
			return Mouse::getPosition(relativeTo);
		}
		return lastRelativeMcPos;
	}
};