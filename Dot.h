#pragma once
#include "Vector2.h"
#define CANVAS_HEIGHT 1079
#define CANVAS_WIDTH 1919
#define groundFriction 0.7
class Dot {
public:
	Vector2 pos;
	Vector2 oldpos;
	float friction = 0.97;
	Vector2 gravity = Vector2(0, 1);
	float radius;
	float mass;
	bool pinned;
	bool visible = true;
	Dot(float x, float y,float mass, float radius, bool pinned) {
		this->pinned = pinned;
		pos = Vector2(x, y);
		oldpos = Vector2(x, y);
		this->radius = radius;
		this->mass = mass;
	}
	void update() {
		if (!pinned) {
			Vector2 vel = pos - oldpos;
			vel *= friction;
			vel += gravity;
			// if the point touches the ground set groundFriction
			if (pos.Y >= CANVAS_HEIGHT - radius && vel.LengthSq() > 0.000001) {
				float m = vel.Length();
				vel.X /= m;
				vel.Y /= m;
				vel *= (m * groundFriction);
			}
			oldpos = pos;
			pos += vel;
		}
	}
	void constrain() {

		if (pos.X > CANVAS_WIDTH - radius)
			pos.X = CANVAS_WIDTH - radius;

		if (pos.X < radius)
			pos.X = radius;

		if (pos.Y > CANVAS_HEIGHT - radius)
			pos.Y = CANVAS_HEIGHT - radius;
			

		if (pos.Y < radius)
			pos.Y = radius;
		

	}
};