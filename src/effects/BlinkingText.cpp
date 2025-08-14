#include "BlinkingText.h"

BlinkingText::BlinkingText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color)
	: renderer(renderer), font(font), text(text), color(color), visible(true), timer(0.0f) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
}

BlinkingText::~BlinkingText() {
	SDL_DestroyTexture(texture);
}

void BlinkingText::setPosition(int x, int y) {
	rect.x = x;
	rect.y = y;
}

void BlinkingText::update(float deltaTime) {
	timer += deltaTime;
	if (timer >= 0.5f) {
		visible = !visible;
		timer = 0.0f;
	}
}

void BlinkingText::render() {
	if (visible) {
		SDL_RenderCopy(renderer, texture, nullptr, &rect);
	}
}