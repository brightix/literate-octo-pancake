#include "pch.h"
#include "textRenderer.h"

TextRenderer& TextRenderer::getInstance() {
	static TextRenderer instance;
	return instance;
}

void TextRenderer::setFont(const string& type,int size) {
	font = ResourceManager::getInstance().getFont(type, size);
}

void TextRenderer::setColor(Uint8 R, Uint8 G, Uint8 B, Uint8 A) {
	textColor = {R,G,B,A};
}



SDL_Texture* TextRenderer::getTextTexture(const char* str) {
	SDL_Surface* textSurface = TTF_RenderText_Blended(font,str, 0, textColor);
	if (!textSurface) {
		std::cerr << "textSurface 创建失败" << std::endl;
	}
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(render, textSurface);
	SDL_DestroySurface(textSurface);
	return textTexture;
}

void TextRenderer::renderText(float x, float y, SDL_Texture* texture) {
	float w, h;
	SDL_GetTextureSize(texture,&w,&h);
	SDL_FRect textRect = { x,y,w,h };
	SDL_RenderTexture(render, texture,nullptr,&textRect);
}

TextRenderer::TextRenderer() {
	TTF_Init();
	setFont("pixel_10", 75);
	setColor(255,255,255,255);
	render = RendererManager::getInstance().getRenderer();
}

TextRenderer::~TextRenderer()
{
	cout << "文字渲染器单例已关闭" << endl;
}
