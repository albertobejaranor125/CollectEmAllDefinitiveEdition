#pragma once
#include "Enemy.h"
#include <SDL.h>
#include <vector>
extern int enemiesToSpawn;
extern int currentWave;
extern bool waveInProgress;
extern Uint32 waveStartTime;
extern Uint32 lastWaveTime;
bool IsTooClose(const SDL_Rect& a, const SDL_Rect& b, int minDistance);
void StartWave(std::vector<Enemy>& enemies, int& enemiesPerLevel, SDL_Rect& playerRect);