#pragma once
#include "GameState.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
struct Button {
    SDL_Rect rect;
    SDL_Color color;
    std::string text;
};
bool Init(SDL_Window** window, SDL_Renderer** renderer, int w, int h);
SDL_Texture* LoadTexture(const std::string& path, SDL_Renderer* renderer);
SDL_Texture* RenderText(const std::string& msg, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
void RenderHUD(SDL_Renderer* renderer, TTF_Font* font, int score, int level, int lives, int highScore, int currentWave,
    SDL_Texture* heartTex, Uint32 gameStartTime, int timeLimit, GameState gameState);
void RenderButton(SDL_Renderer* renderer, TTF_Font* font, Button btn, bool hovered);
