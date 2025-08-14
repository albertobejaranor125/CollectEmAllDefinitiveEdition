#pragma once
#include <SDL.h>

class DamageFlash {
private:
	SDL_Renderer* renderer;
	float alpha;

public:
	DamageFlash(SDL_Renderer* renderer);
	void trigger();
	void update(float deltaTime);
	void render();
};