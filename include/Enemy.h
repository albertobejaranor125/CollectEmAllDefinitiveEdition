#pragma once
#include "Projectile.h"
#include "Score.h"
#include <SDL.h>
#include <vector>
enum EnemyType{SLOW, FAST, RANGED};
struct Enemy {
    SDL_Rect rect;
    float vx, vy;
    EnemyType type;
};
void SpawnEnemy(std::vector<Enemy>& enemies, int screenW, int screenH);
Enemy SpawnEnemyTemp(int screenW, int screenH);
void UpdateEnemies(std::vector<Enemy>& enemies, float dt, int screenW, int screenH, SDL_Rect player, int level, int& score, int& highScore, Uint32& lastShootTime, Uint32& shootInterval, std::vector<Projectile>& projectiles);