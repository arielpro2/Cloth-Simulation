#pragma once
#include "Dot.h"
class Stick {
public:
	Dot* startPoint;
	Dot* endPoint;
	float length;
	float stiffness = 3;
	float breakingLength;
	bool visible = true;
	bool broken = false;
	Stick(Dot* p1, Dot* p2,float breakingRatio, float length) {
		startPoint = p1;
		endPoint = p2;
		this->length = length;
		this->breakingLength = breakingRatio*length;
	}
	Stick(Dot* p1, Dot* p2, float breakingRatio) {
		startPoint = p1;
		endPoint = p2;
		this->length = p1->pos.Distance(p2->pos);
		this->breakingLength = breakingRatio * length;
	}
	void update() {
		// calculate the distance between two dots
		Vector2 delta = endPoint->pos - startPoint->pos;
		float dist = delta.Length();
		if (dist >= breakingLength)
			broken = true;
		// calculate the resting distance betwen the dots
		float diff = (length - dist) / dist * stiffness;

		// getting the offset of the points
		Vector2 offset = delta * diff * 0.5;

		// calculate mass
		float m1 = startPoint->mass + endPoint->mass;
		float m2 = startPoint->mass / m1;
		m1 = endPoint->mass / m1;

		// and finally apply the offset with calculated mass
		if (!startPoint->pinned) {
			startPoint->pos -= offset * m1;
		}
		if (!endPoint->pinned) {
			endPoint->pos += offset * m2;
		}
	}
};