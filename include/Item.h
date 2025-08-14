#ifndef ITEM_H
#define ITEM_H
#include <SDL.h>
#include "Score.h"
void HandleItemCollision(SDL_Rect& playerRect, SDL_Rect& itemRect, int screenW, int screenH,
	int& score, int& level, int& highScore);
#endif // !ITEM_H

