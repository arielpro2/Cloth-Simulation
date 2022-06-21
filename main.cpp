#pragma once

#include <vector>
#include "Entity.h"


SDL_Window* window = SDL_CreateWindow("Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CANVAS_WIDTH, CANVAS_HEIGHT, SDL_WINDOW_SHOWN);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

using namespace std;

Entity createCloth(int posx, int posy, int w, int h, int segments) {
	Entity cloth = Entity(16);
	int xStride = w / segments;
	int yStride = h / segments;
	for (int y = 0; y < segments; ++y)
	{
		for (int x = 0; x < segments; ++x)
		{
			int px = posx + x * xStride - w / 2 + xStride / 2;
			int py = posy + y * yStride - h / 2 + yStride / 2;
			cloth.addDot(px, py,1,1,false);
		}
	}
	for (int y = 0; y < segments; ++y)
	{
		for (int x = 0; x < segments; ++x)
		{
			if (x > 0) {
				cloth.addStick(y * segments + x, y * segments + x - 1,5);
			}
			if (y > 0) {
				cloth.addStick(y * segments + x, (y - 1) * segments + x,5);
			}
		}
	}
	for (int i = 0; i < segments; i+=4)
	{
		cloth.dots[i].pinned = true;
	}
	return cloth;
}
void Simulation() {
	Entity Cloth = createCloth(CANVAS_WIDTH/2, CANVAS_HEIGHT/4, CANVAS_WIDTH/2, CANVAS_HEIGHT/2, 50);
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	while (1) {
		SDL_PollEvent(&event);
		if (state[SDL_SCANCODE_R]) {
			Cloth = createCloth(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH/2, CANVAS_HEIGHT/2, 50);
		}
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);
		int x, y;
		SDL_GetGlobalMouseState(&x, &y);
		int stickIndex = Cloth.getClosestStick(x, y,25);
		if (stickIndex !=-1)
			Cloth.removeStick(stickIndex);
		int dotIndex = Cloth.getClosestDot(x, y, 25);
		if (dotIndex != -1)
			Cloth.removeDot(dotIndex);
		Cloth.update();
		Cloth.render(renderer);
		
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderPresent(renderer);
	}
}

int main(int argc, char** args) {
	srand(time(nullptr));
	SDL_Init(SDL_INIT_EVERYTHING);
	Simulation();
	return 0;
}
