#pragma once
#include "Stick.h"
#include <vector>
#include <SDL.h>

using namespace std;
void DrawFilledCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, x + dx, y + dy);
			}
		}
	}
}
void DrawHollowCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}
class Entity {
public:
	vector<Dot> dots;
	vector<Stick> sticks;
	int iterations;
	Entity(int iterations) {
		this->iterations = iterations;
	}
	void addDot(float x, float y, float mass, float radius, bool pinned, bool visible = true) {
		dots.push_back(Dot(x, y, mass, radius, pinned));
		dots[dots.size() - 1].visible = visible;
	}
	void addStick(int p1, int p2, float breakingRatio,float length, bool visible = true) {
		sticks.push_back(Stick(&dots[p1], &dots[p2], breakingRatio, length));
		dots[dots.size() - 1].visible = visible;
	}
	void addStick(int p1, int p2 , float breakingRatio, bool visible = true) {
		sticks.push_back(Stick(&dots[p1], &dots[p2], breakingRatio));
		sticks[sticks.size() - 1].visible = visible;
	}
	void removeDot(int p) {
		dots[p].visible = false;
		for (int i = 0; i < sticks.size(); i++)
		{
			if (sticks[i].startPoint == &dots[p] || sticks[i].endPoint == &dots[p])
			{
				removeStick(i);
				return;
			}
		}
	}
	void removeStick(int s) {
		sticks.erase(sticks.begin() + s);
	}
	int getClosestDot(float x, float y, float radius) {
		Vector2 pos = Vector2(x, y);
		for (int i = 0; i < dots.size(); i++)
		{
			float dist = pos.Distance(dots[i].pos);
			if (dist - dots[i].radius < radius)
				return i;
		}
		return -1;
	}
	int getClosestStick(float x, float y, float radius) {
		Vector2 pos = Vector2(x, y);
		for (int i = 0; i < sticks.size(); i++)
		{
			float d1 = pos.Distance(sticks[i].startPoint->pos);
			float d2 = pos.Distance(sticks[i].endPoint->pos);

			float lineLen = sticks[i].startPoint->pos.Distance(sticks[i].endPoint->pos);

			float buffer = radius;

			if (d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer)
				return i;
		}
		return -1;
	}
	void updateDots() {
		for (int i = 0; i < dots.size(); i++)
		{
			dots[i].update();
		}
	}
	void updateSticks() {
		for (int i = 0; i < sticks.size(); i++)
		{
			sticks[i].update();
			
		}
	}
	void updateContrainsts() {
		for (int i = 0; i < dots.size(); i++)
		{
			dots[i].constrain();
		}
	}
	void renderDots(SDL_Renderer* renderer) {
		for (int i = 0; i < dots.size(); i++)
		{
			if (dots[i].visible)
				DrawFilledCircle(renderer, dots[i].pos.X, dots[i].pos.Y, dots[i].radius);
		}
	}
	void renderSticks(SDL_Renderer* renderer) {
		for (int i = 0; i < sticks.size(); i++)
		{
			if (sticks[i].visible)
				SDL_RenderDrawLine(renderer, sticks[i].startPoint->pos.X, sticks[i].startPoint->pos.Y, sticks[i].endPoint->pos.X, sticks[i].endPoint->pos.Y);
		}
	}
	void update() {
		updateDots();
		for (int i = 0; i < iterations; i++)
		{
			updateSticks();
			updateContrainsts();
		}
		for (int i = 0; i < sticks.size(); i++)
		{
			if (sticks[i].broken)
			{
				removeStick(i);
				i--;
			}
		}
	}
	void render(SDL_Renderer* renderer) {
		renderDots(renderer);
		renderSticks(renderer);
	}
};