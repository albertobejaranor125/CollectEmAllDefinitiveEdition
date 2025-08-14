#include "Player.h"
SDL_Rect playerRect = { 368,300,64,64 };
bool isInvulnerable = false;
Uint32 invulnerableStart = 0;
const int invulnerableDuration = 1000; //ms
void UpdatePlayer(Uint32 now) {
	if (isInvulnerable && (now - invulnerableStart >= invulnerableDuration)) {
		isInvulnerable = false;
	}
}
void RenderPlayer(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, 
	int frameHeight, int currentFrame) {
    if (isInvulnerable && ((SDL_GetTicks() / 100) % 2 == 0)) {
        SDL_SetTextureAlphaMod(texture, 120);
    }
    else {
        SDL_SetTextureAlphaMod(texture, 255);
    }
	SDL_Rect srcRect = { currentFrame * frameWidth, 0, frameWidth, frameHeight };
	SDL_RenderCopy(renderer, texture, &srcRect, &playerRect);
}