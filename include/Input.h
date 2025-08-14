#ifndef INPUT_H
#define INPUT_H
#include <SDL.h>
#include "GameState.h"
void HandlePlayerInput(const SDL_Event& event, SDL_Rect& playerRect, int speed, GameState gameState);
#endif // !INPUT_H

