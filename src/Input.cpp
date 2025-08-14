#include "Input.h"
void HandlePlayerInput(const SDL_Event& event, SDL_Rect& playerRect, int speed, GameState gameState) {
	if (event.type == SDL_KEYDOWN && gameState == PLAYING) {
		SDL_Keycode pressed = event.key.keysym.sym;
		if (pressed == SDLK_w) playerRect.y -= speed;
		if (pressed == SDLK_s) playerRect.y += speed;
		if (pressed == SDLK_a) playerRect.x -= speed;
		if (pressed == SDLK_d) playerRect.x += speed;
	}
}