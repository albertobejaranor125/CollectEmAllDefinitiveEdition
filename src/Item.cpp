#include "Item.h"
#include <cstdlib>
void HandleItemCollision(SDL_Rect& playerRect, SDL_Rect& itemRect, int screenW, int screenH,
	int& score, int& level, int& highScore) {
    if (SDL_HasIntersection(&playerRect, &itemRect)) {
        score += 10;
        itemRect.x = rand() % (screenW - itemRect.w);
        itemRect.y = rand() % (screenH - itemRect.h);

        if (score % 30 == 0) {
            level++;
        }

        if (score > highScore) {
            highScore = score;
            SaveHighScore();
        }
    }
}