#pragma once
#include <SDL.h>
#include <vector>
struct Projectile {
    SDL_Rect rect;
    float vx, vy;
};
void UpdateProjectiles(std::vector<Projectile>& projectiles, float dt, int screenW, int screenH, SDL_Rect& playerRect, int& lives, bool& isInvulnerable, Uint32& invulnerableStart);