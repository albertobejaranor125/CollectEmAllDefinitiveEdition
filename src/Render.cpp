#include "Render.h"

bool Init(SDL_Window** window, SDL_Renderer** renderer, int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    if (TTF_Init() == -1) return false;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return false;

    *window = SDL_CreateWindow("Etapa 12", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    return *window && *renderer;
}
SDL_Texture* LoadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Error loading texture: " << path << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
SDL_Texture* RenderText(const std::string& msg, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, msg.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
void RenderHUD(SDL_Renderer* renderer, TTF_Font* font, int score, int level, int lives, int highScore, int currentWave,
    SDL_Texture* heartTex, Uint32 gameStartTime, int timeLimit, GameState gameState) {
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Texture* scoreTex = RenderText("Score: " + std::to_string(score), font, white, renderer);
    SDL_Rect dest = { 20, 20, 0, 0 };
    SDL_QueryTexture(scoreTex, nullptr, nullptr, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, scoreTex, nullptr, &dest);
    SDL_DestroyTexture(scoreTex);

    SDL_Texture* levelTex = RenderText("Level: " + std::to_string(level), font, white, renderer);
    SDL_Rect lRect = { 200,100,0,0 };
    SDL_QueryTexture(levelTex, nullptr, nullptr, &lRect.w, &lRect.h);
    SDL_RenderCopy(renderer, levelTex, nullptr, &lRect);
    SDL_DestroyTexture(levelTex);
    for (int i = 0; i < lives; i++) {
        SDL_Rect heartRect = { 20 + i * 40, 60, 32, 32 };
        SDL_RenderCopy(renderer, heartTex, nullptr, &heartRect);
    }

    if (gameState == PLAYING) {
        Uint32 now = SDL_GetTicks();
        int timeLeft = timeLimit - (now - gameStartTime) / 1000;
        if (timeLeft < 0) timeLeft = 0;

        SDL_Texture* timeTex = RenderText("Time: " + std::to_string(timeLeft), font, white, renderer);
        SDL_Rect tRect = { 700,20,0,0 };
        SDL_QueryTexture(timeTex, nullptr, nullptr, &tRect.w, &tRect.h);
        SDL_RenderCopy(renderer, timeTex, nullptr, &tRect);
        SDL_DestroyTexture(timeTex);
    }

    SDL_Texture* highTex = RenderText("High Score: " + std::to_string(highScore), font, white, renderer);
    SDL_Rect hRect = { 20,100,0,0 };
    SDL_QueryTexture(highTex, nullptr, nullptr, &hRect.w, &hRect.h);
    SDL_RenderCopy(renderer, highTex, nullptr, &hRect);
    SDL_DestroyTexture(highTex);

    SDL_Texture* waveTex = RenderText("Wave: " + std::to_string(currentWave), font, white, renderer);
    SDL_Rect wRect = { 600,60,0,0 };
    SDL_QueryTexture(waveTex, nullptr, nullptr, &wRect.w, &wRect.h);
    SDL_RenderCopy(renderer, waveTex, nullptr, &wRect);
    SDL_DestroyTexture(waveTex);
}
void RenderButton(SDL_Renderer* renderer, TTF_Font* font, Button btn, bool hovered) {
    SDL_Color color;
    if (hovered) {
        color.r = (Uint8)std::min(255, btn.color.r + 40);
        color.g = (Uint8)std::min(255, btn.color.g + 40);
        color.b = (Uint8)std::min(255, btn.color.a + 40);
        color.a = 255;
    }
    else {
        color = btn.color;
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &btn.rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &btn.rect);

    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Texture* tex = RenderText(btn.text, font, white, renderer);
    int texW = 0, texH = 0;
    SDL_QueryTexture(tex, nullptr, nullptr, &texW, &texH);
    SDL_Rect textRect{
        btn.rect.x + (btn.rect.w - texW) / 2,
        btn.rect.y + (btn.rect.h - texH) / 2,
        texW, texH
    };
    SDL_RenderCopy(renderer, tex, nullptr, &textRect);
    SDL_DestroyTexture(tex);
}