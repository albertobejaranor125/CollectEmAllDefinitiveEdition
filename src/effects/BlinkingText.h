#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class BlinkingText {
private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Color color;
	std::string text;
	SDL_Texture* texture;
	SDL_Rect rect;
	bool visible;
	float timer;

public:
	BlinkingText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color);
	~BlinkingText();

	void setPosition(int x, int y);
	void update(float deltaTime);
	void render();
};