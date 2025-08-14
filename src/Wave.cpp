#include "Wave.h"
#include <algorithm>
int enemiesToSpawn = 0;
int currentWave = 1;
bool waveInProgress = false;
Uint32 waveStartTime = 0;
Uint32 lastWaveTime = 0;
extern void SpawnEnemy(std::vector<Enemy>& enemies, int screenW, int screenH);
static inline int Dist2(const SDL_Rect& a, const SDL_Rect& b) {
    int dx = (a.x + a.w / 2) - (b.x + b.w / 2);
    int dy = (a.y + a.h / 2) - (b.y + b.h / 2);
    return dx * dx + dy * dy;
}
bool IsTooClose(const SDL_Rect& a, const SDL_Rect& b, int minDistance) {
    const int md2 = minDistance * minDistance;
    return Dist2(a, b) < md2;
}
void StartWave(std::vector<Enemy>& enemies, int& enemiesPerLevel, SDL_Rect& playerRect) {
    enemies.clear();
    enemiesToSpawn = enemiesPerLevel;
    const int MIN_DIST_PLAYER = 80;
    const int MIN_DIST_ENEMIES = 50;
    for (int i = 0; i < enemiesToSpawn; i++) {
        bool placed = false;
        int tries = 0;
        while (!placed && tries < 50) {
            SpawnEnemy(enemies, 800, 600);
            Enemy& e = enemies.back();
            if (IsTooClose(e.rect, playerRect, MIN_DIST_PLAYER)) {
                enemies.pop_back();
                tries++;
                continue;
            }
            bool tooClose = false;
            for (size_t k = 0; k + 1 < enemies.size(); k++) {
                if (IsTooClose(e.rect, enemies[k].rect, MIN_DIST_ENEMIES)) {
                    tooClose = true;
                    break;
                }
            }
            if (tooClose) {
                enemies.pop_back();
                tries++;
                continue;
            }
            placed = true;
            if (!placed) {
                break;
            }
        }
    }
    waveInProgress = true;
    waveStartTime = SDL_GetTicks();
    lastWaveTime = waveStartTime;
    currentWave++;
}