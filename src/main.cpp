#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include "Enemy.h"
#include "Projectile.h"
#include "Render.h"
#include "GameState.h"
#include "Score.h"
#include "Wave.h"
#include "Input.h"
#include "Item.h"
#include "Player.h"
#include "effects/FadeEffect.h"
#include "effects/DamageFlash.h"
#include "effects/BlinkingText.h"
int score = 0;
int lives = 3;
int level = 1;
SDL_Texture* heartTex = nullptr;

SDL_Rect itemRect = { 400,400,32,32 };
SDL_Texture* itemTex = nullptr;
const int playerSpeed = 50;

Uint32 gameStartTime = 0;
int timeLimit = 30;

std::vector<Enemy> enemies;
int enemiesPerLevel = 2;
float enemyBaseSpeed = 80.0f;

Uint32 waveDelay = 3000; //ms

std::vector<Projectile> projectiles;
Uint32 lastShootTime = 0;
Uint32 shootInterval = 2000; //ms
int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* spritesheet = nullptr;
    if (!Init(&window, &renderer, 800, 600)) return 1;

    TTF_Font* font = TTF_OpenFont("assets/font.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font\n";
        return 1;
    }
    Button playButton = { {300,250,200,60}, {0,120,255}, "PLAY" };
    Button restartButton = { {300,330,200,60}, {0,200,100}, "RESTART" };
    bool running = true;
    SDL_Event event;
    Uint32 lastTick = SDL_GetTicks();

    heartTex = LoadTexture("assets/heart.png", renderer);
    if (!heartTex) return 1;

    spritesheet = LoadTexture("assets/spritesheet.png", renderer);
    if (!spritesheet) return 1;

    itemTex = LoadTexture("assets/coin.png", renderer);
    if (!itemTex) return 1;

    const int frameWidth = 64;
    const int frameHeight = 64;
    const int numFrames = 4;
    int currentFrame = 0;
    Uint32 frameDuration = 150;
    Uint32 lastFrameTime = SDL_GetTicks();

    Mix_Music* bgMusic = Mix_LoadMUS("assets/music.ogg");
    Mix_Chunk* correctSound = Mix_LoadWAV("assets/correct.wav");
    Mix_Chunk* wrongSound = Mix_LoadWAV("assets/wrong.wav");
    Mix_Chunk* winSound = Mix_LoadWAV("assets/victory.wav");
    Mix_Chunk* gameoverSound = Mix_LoadWAV("assets/gameover.wav");
    if (!bgMusic || !correctSound || !wrongSound || !winSound || !gameoverSound) return 1;

    srand(static_cast<unsigned>(time(nullptr)));


    LoadHighScore();

    FadeEffect fade(renderer);
    BlinkingText blinkingText(renderer, font, "Avoid the enemies!", { 0, 255, 255, 255 });
    DamageFlash damageFlash(renderer);
    //Playing game
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int x = event.button.x;
                int y = event.button.y;
                SDL_Point clickPoint = { x,y };

                switch (gameState) {
                case MENU:
                    if (SDL_PointInRect(&clickPoint, &playButton.rect)) {
                        fade.startFadeIn(2000);
                        gameState = PLAYING;
                        score = 0;
                        lives = 3;
                        level = 1;
                        currentWave = 1;
                        enemies.clear();
                        StartWave(enemies, enemiesPerLevel, playerRect);
                        gameStartTime = SDL_GetTicks();


                    }
                    break;
                case GAME_OVER:
                    if (SDL_PointInRect(&clickPoint, &restartButton.rect)) {
                        score = 0;
                        lives = 3;
                        level = 1;
                        enemies.clear();
                        isInvulnerable = false;
                        waveInProgress = true;
                        currentWave = 1;
                        gameState = MENU;
                    }
                    break;
                case VICTORY:
                    if (SDL_PointInRect(&clickPoint, &restartButton.rect)) {
                        score = 0;
                        lives = 3;
                        level = 1;
                        enemies.clear();
                        isInvulnerable = false;
                        waveInProgress = true;
                        currentWave = 1;
                        gameState = MENU;
                    }
                    break;
                }
            }
            if (event.type == SDL_KEYDOWN) {
                switch (gameState) {
                case PLAYING: {
                    
                    timeLimit = 30 - (level - 1) * 5;
                    if (timeLimit < 10) timeLimit = 10;
                    Uint32 now = SDL_GetTicks();
                    int timeLeft = timeLimit - (now - gameStartTime) / 1000;
                    if (timeLeft <= 0) {
                        Mix_HaltMusic();
                        Mix_PlayChannel(-1, gameoverSound, 0);
                        gameState = GAME_OVER;
                    }
                    if (event.key.keysym.sym == SDLK_p) {
                        gameState = PAUSED;
                    }
                    HandlePlayerInput(event, playerRect, playerSpeed, gameState);

                    HandleItemCollision(playerRect, itemRect, 800, 600, score, level, highScore);
                    if (!isInvulnerable) {
                        for (auto& e : enemies) {
                            if (SDL_HasIntersection(&playerRect, &e.rect)) {
                                lives--;
                                Mix_PlayChannel(-1, wrongSound, 0);
                                isInvulnerable = true;
                                invulnerableStart = SDL_GetTicks();
                                damageFlash.trigger();

                                if (lives <= 0) {
                                    Mix_HaltMusic();
                                    Mix_PlayChannel(-1, gameoverSound, 0);
                                    gameState = GAME_OVER;
                                }
                                break;
                            }
                        }
                    }
                    UpdatePlayer(SDL_GetTicks());
                    break;
                }
                case PAUSED:
                    if (event.key.keysym.sym == SDLK_p) {
                        gameState = PLAYING;
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        gameState = MENU;
                    }
                    break;
                }
            }
        }

        Uint32 nowTicks = SDL_GetTicks();
        Uint32 deltaMs = nowTicks - lastTick;
        float dt = deltaMs / 1000.0f;
        lastTick = nowTicks;

        if (waveInProgress) {
            Uint32 now = SDL_GetTicks();
            if (now - waveStartTime >= waveDelay) {
                //currentWave++;
                enemiesPerLevel = 2 + (level - 1) / 2;
                score += 20;
                StartWave(enemies, enemiesPerLevel, playerRect);
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);
        //Rendering game
        switch (gameState) {
        case MENU: {
            int mx, my;
            SDL_GetMouseState(&mx, &my);
            SDL_Point mousePoint = { mx, my };

            bool hoveredPlay = SDL_PointInRect(&mousePoint, &playButton.rect);
            RenderButton(renderer, font, playButton, hoveredPlay);
            break;
        }
        case PLAYING: {
            RenderHUD(renderer, font, score, level, lives, highScore, currentWave, heartTex, gameStartTime, timeLimit, gameState);
            UpdateEnemies(enemies, dt, 800, 600, playerRect, level, score, highScore, lastShootTime, 
                shootInterval, projectiles);
            UpdateProjectiles(projectiles, dt, 800, 600, playerRect, lives, isInvulnerable, invulnerableStart);
            
            blinkingText.setPosition(300, 100);
            blinkingText.update(static_cast<float>(deltaMs));
            blinkingText.render();
            
            Uint32 now = SDL_GetTicks();
            if (now - lastFrameTime >= frameDuration) {
                currentFrame = (currentFrame + 1) % numFrames;
                lastFrameTime = now;
            }
            SDL_Rect dstRect = { 368, 300, frameWidth, frameHeight };
            RenderPlayer(renderer, spritesheet, frameWidth, frameHeight, currentFrame);
            SDL_RenderCopy(renderer, itemTex, nullptr, &itemRect);
            for (auto& e : enemies) {
                switch (e.type) {
                case RANGED: SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); break;
                case SLOW: SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255); break;
                case FAST: SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break;
                }
                SDL_RenderFillRect(renderer, &e.rect);
            }
            for (auto& p : projectiles) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &p.rect);
            }

            static float itemOffset = 0.0f;
            static float itemSpeed = 0.5f;
            itemOffset += itemSpeed;
            if (itemOffset > 5.0f || itemOffset < -5.0f) itemSpeed = -itemSpeed;

            SDL_Rect animatedItemRect = itemRect;
            animatedItemRect.y += (int)itemOffset;
            SDL_RenderCopy(renderer, itemTex, nullptr, &animatedItemRect);

            fade.update(static_cast<float>(deltaMs));
            fade.render();

            damageFlash.update(static_cast<float>(deltaMs));
            damageFlash.render();
            break;
        }
        case VICTORY: {
            SDL_Color c = { 0, 255, 0, 255 };
            SDL_Texture* t = RenderText("You Win!", font, c, renderer);
            SDL_Rect r = { 150, 250, 0, 0 };
            SDL_QueryTexture(t, nullptr, nullptr, &r.w, &r.h);
            SDL_RenderCopy(renderer, t, nullptr, &r);
            SDL_DestroyTexture(t);

            int mx, my;
            SDL_GetMouseState(&mx, &my);
            SDL_Point mousePoint = { mx, my };

            bool hoveredRestart = SDL_PointInRect(&mousePoint, &restartButton.rect);
            RenderButton(renderer, font, restartButton, hoveredRestart);
            break;
        }
        case GAME_OVER: {
            SDL_Color c = { 255, 0, 0, 255 };
            SDL_Texture* t = RenderText("Game Over", font, c, renderer);
            SDL_Rect r = { 150, 250, 0, 0 };
            SDL_QueryTexture(t, nullptr, nullptr, &r.w, &r.h);
            SDL_RenderCopy(renderer, t, nullptr, &r);
            SDL_DestroyTexture(t);

            int mx, my;
            SDL_GetMouseState(&mx, &my);
            SDL_Point mousePoint = { mx, my };

            bool hoveredRestart = SDL_PointInRect(&mousePoint, &restartButton.rect);
            RenderButton(renderer, font, restartButton, hoveredRestart);
            break;
        }
        case PAUSED: {
            SDL_Color c = { 255, 255, 255, 255 };
            SDL_Texture* t = RenderText("Game Paused. Press P to Resume or ESC to Menu", font, c, renderer);
            SDL_Rect r = { 100, 250, 0, 0 };
            SDL_QueryTexture(t, nullptr, nullptr, &r.w, &r.h);
            SDL_RenderCopy(renderer, t, nullptr, &r);
            SDL_DestroyTexture(t);
            break;
        }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    Mix_FreeMusic(bgMusic);
    Mix_FreeChunk(correctSound);
    Mix_FreeChunk(wrongSound);
    Mix_FreeChunk(winSound);
    Mix_FreeChunk(gameoverSound);
    Mix_CloseAudio();
    TTF_CloseFont(font);
    SDL_DestroyTexture(heartTex);
    SDL_DestroyTexture(itemTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}