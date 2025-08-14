#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
extern SDL_Rect playerRect;
extern bool isInvulnerable;
extern Uint32 invulnerableStart;
extern const int invulnerableDuration;
void UpdatePlayer(Uint32 now);
void RenderPlayer(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, 
	int frameHeight, int currentFrame);
#endif // !PLAYER_H

