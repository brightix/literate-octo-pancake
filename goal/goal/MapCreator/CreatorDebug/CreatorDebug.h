#pragma once
#include "pch.h"

class CreatorDebug
{
public:
	inline void printInfo(const string& name ,SDL_FRect rect,int no) {
        int size = 20;
        TextRenderer& textRenderer = TextRenderer::Instance();
        shared_ptr<SDL_Texture> texture = textRenderer.getTextTexture(
            to_string(no) + 
            ". " +
            name +
            " = {" +
            to_string((int)rect.x) + " " +
            to_string((int)rect.y) + " " +
            to_string((int)rect.w) + " " +
            to_string((int)rect.h) + " " + "}",
            "pingfang", size);
        textRenderer.renderText(0, Resolution::Instance().getWindowRect().h - no * size, texture.get());
	}
};

