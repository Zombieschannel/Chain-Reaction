#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Distance
{
	Distance() {};
	Distance(const Distance&) = delete;
public:
	static float Point_Circle(const sf::Vector2f& pos1, const sf::Vector2f& pos2, const float radius2)
	{
		return sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y)) - radius2;
	}
	static float Point_Circle(const sf::Vector2f& point1, const sf::CircleShape& circle2)
	{
		return sqrt((point1.x - circle2.getPosition().x) * (point1.x - circle2.getPosition().x)
			+ (point1.y - circle2.getPosition().y) * (point1.y - circle2.getPosition().y)) - circle2.getRadius();
	}
	static float Point_Point(const sf::Vector2f& pos1, const sf::Vector2f& pos2)
	{
		return sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
	}
	static float Point_Rectangle(const sf::Vector2f& pos1, const sf::RectangleShape& rectangle)
	{
		Vector2f tests = pos1;
		if (pos1.x < rectangle.getPosition().x)
			tests.x = rectangle.getPosition().x;
		else if (pos1.x > rectangle.getPosition().x + rectangle.getSize().x)
			tests.x = rectangle.getPosition().x + rectangle.getSize().x;

		if (pos1.y < rectangle.getPosition().y)
			tests.y = rectangle.getPosition().y;
		else if (pos1.y > rectangle.getPosition().y + rectangle.getSize().y)
			tests.y = rectangle.getPosition().y + rectangle.getSize().y;

		Vector2f dist = Vector2f(pos1.x - tests.x, pos1.y - tests.y);
		float distanceSqr = (dist.x * dist.x) + (dist.y * dist.y);
		return sqrt(distanceSqr);
	}
	static float Point_Rectangle(const sf::Vector2f& pos1, const sf::FloatRect& rectangle)
	{

		Vector2f tests = pos1;
		if (pos1.x < rectangle.left)
			tests.x = rectangle.left;
		else if (pos1.x > rectangle.left + rectangle.width)
			tests.x = rectangle.left + rectangle.width;

		if (pos1.y < rectangle.top)
			tests.y = rectangle.top;
		else if (pos1.y > rectangle.top + rectangle.height)
			tests.y = rectangle.top + rectangle.height;

		Vector2f dist = Vector2f(pos1.x - tests.x, pos1.y - tests.y);
		float distanceSqr = (dist.x * dist.x) + (dist.y * dist.y);
		return sqrt(distanceSqr);
	}
private:
	static Distance& Get()
	{
		static Distance instance;
		return instance;
	}

};
class Collision
{
	Collision() {};
	Collision(const Collision&) = delete;
public:
	static bool Circle_Circle(const sf::Vector2f& pos1, const sf::Vector2f& pos2, const float radius1, const float radius2)
	{
		if ((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y) <= (radius1 + radius2) * (radius1 + radius2))
			return 1;
		return 0;
	}
	static bool Circle_Circle(const sf::CircleShape& circle1, const sf::CircleShape& circle2)
	{
		if ((circle1.getPosition().x - circle2.getPosition().x) * (circle1.getPosition().x - circle2.getPosition().x)
			+ (circle1.getPosition().y - circle2.getPosition().y) * (circle1.getPosition().y - circle2.getPosition().y)
			<= (circle1.getRadius() + circle2.getRadius()) * (circle1.getRadius() + circle2.getRadius()))
			return 1;
		return 0;
	}
	static bool Circle_Point(const sf::Vector2f& pos1, const sf::Vector2f& pos2, const float radius1)
	{
		if ((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y) <= (radius1 + 1) * (radius1 + 1))
			return 1;
		return 0;
	}
	static bool Circle_Point(const sf::CircleShape& circle, const sf::Vector2f& pointPos)
	{
		if ((circle.getPosition().x - pointPos.x) * (circle.getPosition().x - pointPos.x) + (circle.getPosition().y - pointPos.y) * (circle.getPosition().y - pointPos.y)
			<= (circle.getRadius() + 1) * (circle.getRadius() + 1))
			return 1;
		return 0;
	}

	static bool Line_Point(const sf::Vector2f LinePoint1, const sf::Vector2f LinePoint2, const sf::Vector2f point)
	{

		float d1 = Distance::Point_Point(point, LinePoint1);
		float d2 = Distance::Point_Point(point, LinePoint2);

		float lineLen = Distance::Point_Point(LinePoint1, LinePoint2);

		float buffer = 0.01;
		if (d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer) {
			return true;
		}
		return false;
	}
	static bool Line_Circle(const sf::CircleShape& circle, const sf::Vector2f point1, const sf::Vector2f point2)
	{
		bool inside1 = Circle_Point(circle, point1);
		bool inside2 = Circle_Point(circle, point2);
		if (inside1 || inside2) return true;
		float distX = point1.x - point2.x;
		float distY = point1.y - point2.y;
		float len = sqrt((distX * distX) + (distY * distY));

		float dot = (((circle.getPosition().x - point1.x) * (point2.x - point1.x)) + ((circle.getPosition().y - point1.y) * (point2.y - point1.y))) / (len * len);

		float closestX = point1.x + (dot * (point2.x - point1.x));
		float closestY = point1.y + (dot * (point2.y - point1.y));

		bool onSegment = Line_Point(point1, point2, Vector2f(closestX, closestY));
		if (!onSegment) return false;
		distX = closestX - circle.getPosition().x;
		distY = closestY - circle.getPosition().y;
		float distance = sqrt((distX * distX) + (distY * distY));
		if (distance <= circle.getRadius()) {
			return true;
		}
		return false;
	}
	static bool Line_Circle(const sf::Vector2f circlePos, const float radius, const sf::Vector2f point1, const sf::Vector2f point2)
	{
		bool inside1 = Circle_Point(circlePos, point1, radius);
		bool inside2 = Circle_Point(circlePos, point2, radius);
		if (inside1 || inside2) return true;
		float distX = point1.x - point2.x;
		float distY = point1.y - point2.y;
		float len = sqrt((distX * distX) + (distY * distY));

		float dot = (((circlePos.x - point1.x) * (point2.x - point1.x)) + ((circlePos.y - point1.y) * (point2.y - point1.y))) / (len * len);

		float closestX = point1.x + (dot * (point2.x - point1.x));
		float closestY = point1.y + (dot * (point2.y - point1.y));

		bool onSegment = Line_Point(point1, point2, Vector2f(closestX, closestY));
		if (!onSegment) return false;
		distX = closestX - circlePos.x;
		distY = closestY - circlePos.y;
		float distance = sqrt((distX * distX) + (distY * distY));
		if (distance <= radius) {
			return true;
		}
		return false;
	}

	static bool Circle_Rectangle(const sf::CircleShape& circle, const sf::RectangleShape& rectangle)
	{
		Vector2f tests = circle.getPosition();
		if (circle.getPosition().x < rectangle.getPosition().x)
			tests.x = rectangle.getPosition().x;
		else if (circle.getPosition().x > rectangle.getPosition().x + rectangle.getSize().x)
			tests.x = rectangle.getPosition().x + rectangle.getSize().x;

		if (circle.getPosition().y < rectangle.getPosition().y)
			tests.y = rectangle.getPosition().y;
		else if (circle.getPosition().y > rectangle.getPosition().y + rectangle.getSize().y)
			tests.y = rectangle.getPosition().y + rectangle.getSize().y;

		Vector2f dist = Vector2f(circle.getPosition().x - tests.x, circle.getPosition().y - tests.y);
		float distanceSqr = (dist.x * dist.x) + (dist.y * dist.y);
		if (distanceSqr <= circle.getRadius() * circle.getRadius())
			return 1;
		return 0;
	}
	static bool Circle_Rectangle(const sf::Vector2f& pos1, const float radius1, const sf::RectangleShape& rectangle)
	{
		return Circle_Rectangle(pos1, radius1, FloatRect(rectangle.getPosition().x, rectangle.getPosition().y, rectangle.getSize().x, rectangle.getSize().y));
	}
	static bool Circle_Rectangle(const sf::Vector2f& pos1, const float radius1, const sf::FloatRect& rectangle)
	{

		Vector2f tests = pos1;
		if (pos1.x < rectangle.left)
			tests.x = rectangle.left;
		else if (pos1.x > rectangle.left + rectangle.width)
			tests.x = rectangle.left + rectangle.width;

		if (pos1.y < rectangle.top)
			tests.y = rectangle.top;
		else if (pos1.y > rectangle.top + rectangle.height)
			tests.y = rectangle.top + rectangle.height;

		Vector2f dist = Vector2f(pos1.x - tests.x, pos1.y - tests.y);
		float distanceSqr = (dist.x * dist.x) + (dist.y * dist.y);
		if (distanceSqr <= radius1 * radius1)
			return 1;
		return 0;
	}
private:
	static Collision& Get()
	{
		static Collision instance;
		return instance;
	}

};