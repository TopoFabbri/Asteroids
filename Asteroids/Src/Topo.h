#pragma once

#include <raylib.h>
#include <cmath>

struct Line
{
	Vector2 start{};
	Vector2 end{};
};

struct Segment3D
{
	Vector3 start{};
	Vector3 end{};
};

struct Circle
{
	Vector2 center;
	float radius;
};

struct Box2D
{
	Rectangle rec{};
	Vector2 vel{};
	float weight{};
};

struct Ball
{
	Circle circ;
	Vector2 vel;
	float weight;
};

void drawLine(Line line, Color color);
void drawCircleCir(Circle circle, Color color);
Vector2 getCirclesCollisionPos(Circle circ1, Circle circ2);
Vector2 getRecsCollisionPos(Rectangle rec1, Rectangle rec2);
float getLength(Line segment);
float getDistanceV3(Segment3D segment);
Vector2 getVector();
Line getLine(Vector2 start);
float getQuadArea(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4);
bool compareVectors(Vector2 v1, Vector2 v2);
bool inRange(float toComp, float min, float max);
bool recCircleColliding(Rectangle rec, Circle cir);
Vector2 getCircleRecCollisionPos(Rectangle rec, Circle circ);
float getVectorMagnitude(Vector2 vec);
Vector2 normalizeVector(Vector2 vec);