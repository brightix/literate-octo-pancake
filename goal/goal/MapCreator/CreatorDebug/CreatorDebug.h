#pragma once
#include "pch.h"

class CreatorDebug
{
public:
    inline void printRectInfo(const string& name, SDL_FRect rect,SDL_FRect showRect, int no) {
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
        textRenderer.renderText(showRect.x, showRect.h - no * size, texture.get());
    }

    template<typename T>
    inline void printText(const string& name,T val,SDL_FPoint pos) {
        auto& tr = TextRenderer::Instance();
        auto texture = tr.getTextTexture(name + to_string(val), "pingfang", 20);
        tr.renderText(pos.x,pos.y, texture.get());
    }

    inline void printMouseXY(SDL_Point pos) {
        auto& tr = TextRenderer::Instance();
        auto texture = tr.getTextTexture(to_string(pos.x) + " " + to_string(pos.x), "pingfang", 20);
        tr.renderText(pos.x+20, pos.y+20, texture.get());
    }
};

