#include "Projectile.h"
void UpdateProjectiles(std::vector<Projectile>& projectiles, float dt, int screenW, int screenH, SDL_Rect& playerRect, int& lives, bool& isInvulnerable, Uint32& invulnerableStart) {
    for (size_t i = 0; i < projectiles.size();) {
        auto& p = projectiles[i];
        p.rect.x += static_cast<int>(p.vx * dt);
        p.rect.y += static_cast<int>(p.vy * dt);
        if (SDL_HasIntersection(&p.rect, &playerRect) && !isInvulnerable) {
            lives--;
            isInvulnerable = true;
            invulnerableStart = SDL_GetTicks();
            projectiles.erase(projectiles.begin() + i);
            continue;
        }
        if (p.rect.x < 0 || p.rect.x > screenW || p.rect.y < 0 || p.rect.y > screenH) {
            projectiles.erase(projectiles.begin() + i);
        }
        else {
            i++;
        }
    }
}