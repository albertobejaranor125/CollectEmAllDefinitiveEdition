#include "DamageFlash.h"

DamageFlash::DamageFlash(SDL_Renderer* renderer)
	: renderer(renderer), alpha(0.0f) { }

void DamageFlash::trigger() {
	alpha = 200;
}

void DamageFlash::update(float deltaTime) {
	if (alpha > 0) {
		alpha -= 300 * deltaTime;
		if (alpha < 0) alpha = 0;
	}
}

void DamageFlash::render() {
	if (alpha <= 0) return;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, (Uint8)alpha);
	SDL_RenderFillRect(renderer, nullptr);
}