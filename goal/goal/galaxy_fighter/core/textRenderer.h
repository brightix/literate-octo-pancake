#pragma once
#include "pch.h"

#pragma execution_character_set("utf-8")

class TextRenderer {
public:
	static TextRenderer& getInstance();

	void setFont(const string& type,int size);

	void setColor(Uint8 R, Uint8 G, Uint8 B, Uint8 A);

	SDL_Texture* getTextTexture(const string& str);

	SDL_Texture* getTextTexture(const string& str, const string& fontType, int size);

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