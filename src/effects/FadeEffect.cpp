#include "FadeEffect.h"

FadeEffect::FadeEffect(SDL_Renderer* renderer)
	: renderer(renderer), duration(1.0f), timer(0.0f), fadingIn(true), fading(false),
	alpha(255) { }

void FadeEffect::startFadeIn(float durationSec) {
	duration = durationSec;
	timer = 0.0f;
	fadingIn = true;
	fading = true;
	alpha = 255;
}

void FadeEffect::startFadeOut(float durationSec) {
	duration = durationSec;
	timer = 0.0f;
	fadingIn = false;
	fading = true;
	alpha = 0;
}

void FadeEffect::update(float deltaTime) {
	if (!fading) return;

	timer += deltaTime;
	float t = timer / duration;
	if (t > 1.0f) {
		t = 1.0f;
		fading = false;
	}
	alpha = fadingIn ? 255 - static_cast<Uint8>(255 * t)
		: static_cast<Uint8>(255 * t);
}

void FadeEffect::render() {
	if (!fading && ((fadingIn && alpha == 0) || (!fadingIn && alpha == 255))) return;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
	SDL_RenderFillRect(renderer, nullptr);
}