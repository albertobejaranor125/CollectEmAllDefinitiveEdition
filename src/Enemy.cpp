#include "Enemy.h"
#include <cmath>
#include <cstdlib> // rand()
#include <algorithm> // for erase
void SpawnEnemy(std::vector<Enemy>& enemies, int screenW, int screenH) {
    Enemy e;
    e.rect = { rand() % (screenW - 32), rand() % (screenH - 32), 32, 32 };
    e.type = static_cast<EnemyType>(rand() % 3);
    float angle = (rand() % 360) * 3.14159f / 180.0f;
    float speed = 0.0f;
    switch (e.type) {
    case SLOW: speed = 50.0f; break;
    case FAST: speed = 150.0f; break;
    case RANGED: speed = 0.0f; break;
    }
    e.vx = cosf(angle) * speed;
    e.vy = sinf(angle) * speed;
    enemies.push_back(e);
}
Enemy SpawnEnemyTemp(int screenW, int screenH) {
    Enemy e;
    e.rect = { rand() % (screenW - 32), rand() % (screenH - 32), 32, 32 };
    e.type = static_cast<EnemyType>(rand() % 3);
    float angle = (rand() % 360) * 3.14159f / 180.0f;
    float speed = 0.0f;
    switch (e.type) {
    case SLOW: speed = 50.0f; break;
    case FAST: speed = 150.0f; break;
    case RANGED: speed = 0.0f; break;
    }
    e.vx = cosf(angle) * speed;
    e.vy = sinf(angle) * speed;
    return e;
}
void UpdateEnemies(std::vector<Enemy>& enemies, float dt, int screenW, int screenH, SDL_Rect player, int level,
    int& score, int& highScore, Uint32& lastShootTime, Uint32& shootInterval, std::vector<Projectile>& projectiles) {
    for (size_t i = 0; i < enemies.size();) {
        Enemy& e = enemies[i];
        if (e.type == SLOW || e.type == FAST) {
            float dx = (float)(player.x + player.w / 2) - (e.rect.x + e.rect.w / 2);
            float dy = (float)(player.y + player.h / 2) - (e.rect.y + e.rect.h / 2);
            float length = sqrtf(dx * dx + dy * dy);
            if (length != 0) {
                dx /= length;
                dy /= length;
            }

            float speed = 80.0f + (level - 1) * 5.0f;
            e.rect.x += static_cast<int>(dx * speed * dt);
            e.rect.y += static_cast<int>(dy * speed * dt);
        } else {
            Uint32 now = SDL_GetTicks();
            if (now - lastShootTime > shootInterval) {
                Projectile p;
                p.rect = { e.rect.x + e.rect.w / 2 - 4, e.rect.y + e.rect.h / 2 - 4 , 8, 8 };
                float dx = (player.x + player.w / 2.0f) - (e.rect.x + e.rect.w / 2.0f);
                float dy = (player.y + player.h / 2.0f) - (e.rect.y + e.rect.h / 2.0f);
                float lengthProjectile = sqrtf(dx * dx + dy * dy);
                if (lengthProjectile != 0) {
                    dx /= lengthProjectile;
                    dy /= lengthProjectile;
                }
                float bulletSpeed = 200.0f;
                p.vx = dx * bulletSpeed;
                p.vy = dy * bulletSpeed;
                projectiles.push_back(p);
                lastShootTime = now;
            }
        }
        if (e.rect.x + e.rect.w < 0 || e.rect.x > screenW ||
            e.rect.y + e.rect.h < 0 || e.rect.y > screenH) {
            enemies.erase(enemies.begin() + i);
            score += 5;
            if (score > highScore) {
                highScore = score;
                SaveHighScore();
            }
        }
        else {
            i++;
        }
    }
}