#pragma once
#include <SDL.h>

class FadeEffect {
private:
	SDL_Renderer* renderer;
	float duration;
	float timer;
	bool fadingIn;
	bool fading;
	Uint8 alpha;

public:
	FadeEffect(SDL_Renderer* renderer);

	void startFadeIn(float durationSec);
	void startFadeOut(float durationSec);
	void update(float deltaTime);
	void render();

	bool isFading() const { return fading; }
};