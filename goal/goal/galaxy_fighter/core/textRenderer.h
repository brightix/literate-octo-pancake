#pragma once
#include "pch.h"
class TextRenderer {
public:
	static TextRenderer& getInstance();

	void setFont(const string& type,int size);

	void setColor(Uint8 R, Uint8 G, Uint8 B, Uint8 A);

	SDL_Texture* getTextTexture(const char* str);

	void renderText(float x, float y, SDL_Texture* texture);

	TextRenderer(const TextRenderer&) = delete;
	TextRenderer& operator=(const TextRenderer&) = delete;
private:
	SDL_Color textColor;
	SDL_Renderer* render;
	TTF_Font* font;
	TextRenderer();
	~TextRenderer();
};