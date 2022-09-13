#include "Topo.h"

void drawCircleCir(Circle circle, Color color)
{
	DrawCircleV(circle.center, circle.radius, color);
}

Vector2 getCirclesCollisionPos(Circle circ1, Circle circ2)
{
	Vector2 midPoint;
	midPoint.x = (circ1.center.x + circ2.center.x) / 2;
	midPoint.y = (circ1.center.y + circ2.center.y) / 2;

	return midPoint;
}

Vector2 getRecsCollisionPos(Rectangle rec1, Rectangle rec2)
{
	Vector2 a1 = { rec1.x, rec1.y };
	Vector2 a2 = { rec1.x + rec1.width, rec1.y + rec1.height };

	Vector2 b1 = { rec2.x, rec2.y };
	Vector2 b2 = { rec2.x + rec2.width, rec2.y + rec2.height };

	Vector2 center1{ (rec1.x + rec1.width) / 2, (rec1.y + rec1.height / 2) };
	Vector2 center2{ (rec2.x + rec2.width) / 2, (rec2.y + rec2.height / 2) };

	float upOffset = center1.y - center2.y;
	float downOffset = upOffset * -1;
	float leftOffset = center1.x - center2.x;
	float rightOffset = leftOffset * -1;

	// Up collision
	if (upOffset > downOffset && upOffset > leftOffset && upOffset > rightOffset)
		return { (b2.x + a1.x) / 2, b1.y };
	// Down collision
	if (downOffset > upOffset && downOffset > leftOffset && downOffset > rightOffset)
		return { (b2.x + a1.x) / 2, b2.y };
	// Left collision
	if (rightOffset > upOffset && rightOffset > downOffset && rightOffset > leftOffset)
		return { b1.x, (b2.y + a1.y) / 2 };
	// Right collision
	if (leftOffset > upOffset && leftOffset > downOffset && leftOffset > rightOffset)
		return { b2.x, (b2.y + a1.y) / 2 };

	return { 0, 0 };
}

float getLength(Line segment)
{
	return sqrtf((segment.start.x - segment.end.x) * (segment.start.x - segment.end.x) +
		(segment.start.y - segment.end.y) * (segment.start.y - segment.end.y));
}

float getDistanceV3(Segment3D segment)
{
	Line lengthXY{ {segment.start.x, segment.start.y}, {segment.end.x, segment.end.y} };

	return getLength({ getLength(lengthXY), (segment.start.z - segment.end.z) * (segment.start.z - segment.end.z) });
}

void drawLine(Line line, Color color)
{
	DrawLineV(line.start, line.end, color);
}

Vector2 getVector()
{
	Vector2 coord;
	do
	{
		coord = GetMousePosition();

	} while (!IsMouseButtonDown(MOUSE_BUTTON_LEFT));

	return coord;
}

Line getLine(Vector2 start)
{
	Line line{ start, GetMousePosition() };

	while (!IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{

		line.end = GetMousePosition();

		BeginDrawing();
		ClearBackground(RED);
		drawLine(line, BLACK);
		EndDrawing();
	}

	return line;
}

float getQuadArea(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4)
{
	float area;
	area = p1.x * p2.y + p2.x * p3.y + p3.x * p4.y + p4.x * p1.y;
	area -= (p2.x * p1.y + p3.x * p2.y + p4.x * p3.y + p1.x * p4.y);
	area /= 2;

	return area;
}

bool compareVectors(Vector2 v1, Vector2 v2)
{
	if (inRange(v1.x - v2.x, -0.5f, 0.5f) && inRange(v1.y - v2.y, -0.5f, 0.5f))
		return true;

	return false;
}

bool inRange(float toComp, float min, float max)
{
	if (toComp <= max && toComp >= min)
		return true;

	return false;
}

bool recCircleColliding(Rectangle rec, Circle cir)
{
	Vector2 tmp{ cir.center.x, cir.center.y };

	if (cir.center.x < rec.x)
		tmp.x = rec.x;
	else if (cir.center.x > rec.x + rec.width)
		tmp.x = rec.x + rec.width;
	if (cir.center.y < rec.y)
		tmp.y = rec.y;
	else if (cir.center.y > rec.y + rec.height)
		tmp.y = rec.y + rec.height;

	Vector2 dist{ cir.center.x - tmp.x, cir.center.y - tmp.y };
	float distance = sqrt((dist.x * dist.x) + (dist.y * dist.y));

	if (distance <= cir.radius)
		return true;

	return false;
}

Vector2 getCircleRecCollisionPos(Rectangle rec, Circle circ)
{
	Vector2 colPos;

	if (recCircleColliding(rec, circ))
	{
		// X straight cases
		if (inRange(circ.center.y, rec.y, rec.y + rec.height))
		{
			colPos.y = circ.center.y;

			// Case left
			if (circ.center.x < rec.x + rec.width / 2)
				colPos.x = circ.center.x + circ.radius;
			// Case right
			else
				colPos.x = circ.center.x - circ.radius;
		}
		// Y straight cases
		else if (inRange(circ.center.x, rec.x, rec.x + rec.width))
		{
			colPos.x = circ.center.x;

			// Case up
			if (circ.center.y < rec.y + rec.height / 2)
				colPos.y = circ.center.y + circ.radius;
			// Case down
			else
				colPos.y = circ.center.y - circ.radius;
		}
		// Upper corner cases
		else if (circ.center.y < rec.y)
		{
			colPos.y = rec.y;

			// Left case
			if (circ.center.x < rec.x + rec.width / 2)
				colPos.x = rec.x;
			// Right case
			else
				colPos.x = rec.x + rec.width;
		}
		// Lower corner cases
		else
		{
			colPos.y = rec.y + rec.height;

			// Left case
			if (circ.center.x < rec.x + rec.height / 2)
				colPos.x = rec.x;
			// Right case
			else
				colPos.x = rec.x + rec.width;

		}
	}
	// No collision case
	else
	{
		colPos = { 0, 0 };
	}
	return colPos;
}