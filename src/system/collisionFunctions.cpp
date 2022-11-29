#include "system/collisionFunctions.h"

#include "Circle.h"
#include  <math.h>

bool isCircleCircleColliding(Circle circle1, Circle circle2)
{

	double distanceX = static_cast<double>(circle1.position.x) - static_cast<double>(circle2.position.x);
	double distanceY = static_cast<double>(circle1.position.y) - static_cast<double>(circle2.position.y);
	double distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

	double totalCircleRadius = static_cast<double>(circle1.radius) + static_cast<double>(circle2.radius);

	if (distance < totalCircleRadius)
	{
		return true;
	}
	return false;

}

bool isPointRecColliding(Vector2 mouse, Rectangle rec)
{
	float rightEdge = rec.x + rec.width;
	float leftEdge = rec.x;
	float upEdge = rec.y;
	float downEdge = rec.y + rec.height;

	if (mouse.x <= rightEdge && mouse.x >= leftEdge && mouse.y >= upEdge && mouse.y <= downEdge)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isRecRecColliding(Rectangle rec, Rectangle rec2)
{

	float rec1RightEdge = rec.x + rec.width;
	float rec1LeftEdge = rec.x;
	float rec1UpEdge = rec.y;
	float rec1DownEdge = rec.y + rec.height;

	float rec2RightEdge = rec2.x + rec2.width;
	float rec2LeftEdge = rec2.x;
	float rec2UpEdge = rec2.y;
	float rec2DownEdge = rec2.y + rec2.height;

	if (rec1RightEdge >= rec2LeftEdge &&
		rec1LeftEdge <= rec2RightEdge &&
		rec1DownEdge >= rec2UpEdge &&
		rec1UpEdge <= rec2DownEdge) {
		return true;
	}
	return false;
}

bool isCircleRecColliding(Circle circle, Rectangle rec)
{

	double testX = circle.position.x;
	double testY = circle.position.y;

	if (circle.position.x < rec.x)         testX = rec.x;
	else if (circle.position.x > rec.x + rec.width) testX = rec.x + rec.width;
	if (circle.position.y < rec.y)         testY = rec.y;
	else if (circle.position.y > rec.y + rec.height) testY = rec.y + rec.height;

	double distX = circle.position.x - testX;
	double distY = circle.position.y - testY;
	double distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= circle.radius) {
		return true;
	}
	return false;
}
