#include "pch.h"
#include "WorldWindow.h"



void WorldWindow::Update()
{

    UpdateInput();
    scaleFactor = showRect.h / camera->getViewport().h;
	DrawBackground();
	DrawInfo();
    DrawSubLine();
    DrawTexture();



}

void WorldWindow::UpdateInput() {
    InputManager& input = InputManager::Instance();
    if (input.isCursorHovering(&showRect) || relativeMouseMode) {
        if (input.isMouseButtonPressed(SDL_BUTTON_MIDDLE)) {
            input.setRelativeMouseMode(relativeMouseMode);
            if (!relativeMouseMode) {
                relativeMouseMode = true;
                return;
            } 
            auto [x,y] = input.getRelativeMousexy();
            camera->addViewport(-x * windowAreaScale,-y * windowAreaScale);
        }
        else if (relativeMouseMode) {
            relativeMouseMode = false;
            input.setRelativeMouseMode(relativeMouseMode);
        }
        else if (int dir = input.isMouseWheelYScrolled()) {
            windowAreaScale = clamp(windowAreaScale + -dir * 0.2, 0.1, 10.0);
            camera->setViewport(BaseViewport.w * windowAreaScale,BaseViewport.h * windowAreaScale);
        }

    }

    if (input.isKeyPressed(SDL_SCANCODE_RIGHT)) {
        camera->addViewport(5, 0);
    }
    if (input.isKeyPressed(SDL_SCANCODE_LEFT)) {
        camera->addViewport(-5, 0);
    }
    if (input.isKeyPressed(SDL_SCANCODE_DOWN)) {
        camera->addViewport(0,5);
    }
    if (input.isKeyPressed(SDL_SCANCODE_UP)) {
        camera->addViewport(0,-5);
    }
}

void WorldWindow::DrawSubLine() {
    auto& textRenderer = TextRenderer::Instance();
    auto color = ColorManager::Instance().getColor(SubLineColor);
    SDL_SetRenderDrawBlendMode(r,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);

    float gap;
    if (windowAreaScale < 3.0f) {
        gap = 300;
    }
    else if (windowAreaScale < 6.0f) {
        gap = 500;
    }
    else {
        gap = 700;
    }
    SDL_FRect viewport = camera->getViewport();
    int i = ceil(viewport.x / gap) * gap;
    float j = viewport.y + viewport.h;
    int n =floor((viewport.x + viewport.w) / gap) * gap;
    int textSize = 10;
    for (i;i <= n;i += gap) {
        SDL_FPoint p1 = camera->worldToViewport_dot(showRect, { (float)i,viewport.y });
        SDL_FPoint p2 = camera->worldToViewport_dot(showRect, { (float)i,j });
        SDL_RenderLine(r, p1.x, p1.y, p2.x, p2.y);

        SDL_FPoint index = camera->worldToViewport_dot(showRect, { (float)i,viewport.y });
        textRenderer.renderText(index.x, index.y, textRenderer.getTextTexture(to_string(i), "pingfang", 10).get());
    }
    
    i = ceil(viewport.y / gap) * gap;
    j = viewport.x + viewport.w;
    n = floor((viewport.y + viewport.h) / gap) * gap;
    for (i;i <= n;i += gap) {
        SDL_FPoint p1 = camera->worldToViewport_dot(showRect, { viewport.x,(float)i });
        SDL_FPoint p2 = camera->worldToViewport_dot(showRect, { j,(float)i });
        SDL_RenderLine(r, p1.x, p1.y, p2.x, p2.y);

        SDL_FPoint index = camera->worldToViewport_dot(showRect, { viewport.x,(float)i });
        textRenderer.renderText(index.x, index.y, textRenderer.getTextTexture(to_string(i), "pingfang", 10).get());
    }
}

void WorldWindow::DrawInfo() {
    auto& textRenderer = TextRenderer::Instance();
    SDL_FPoint p = { placeholderRect.x,placeholderRect.y };
    auto texture = textRenderer.getTextTexture(TO_STRING_2(scaleFactor), "pingfang", 20);
    textRenderer.renderText(p.x, p.y,texture.get());
    
    SDL_FRect viewport = camera->getViewport();
    p.x = p.x + texture->w;
    texture = textRenderer.getTextTexture(
        "viewport = {" + 
        to_string((int)viewport.x) + " " +
        to_string((int)viewport.y) + " " +
        to_string((int)viewport.w) + " " +
        to_string((int)viewport.h) + " " + "}",
        "pingfang", 20);
    textRenderer.renderText(p.x, p.y, texture.get());

    p.x = p.x + texture->w;
    texture = textRenderer.getTextTexture(
        "showRect = {" +
        to_string((int)showRect.x) + " " +
        to_string((int)showRect.y) + " " +
        to_string((int)showRect.w) + " " +
        to_string((int)showRect.h) + " " + "}",
        "pingfang", 20);
    textRenderer.renderText(p.x, p.y, texture.get());
}

void WorldWindow::DrawTexture() {
    for (auto t : textures) {
        if (camera->isOnScreen(showRect,t.rect)) {
            SDL_FRect texShowRect = camera->transformViewportArea(t.rect);
            SDL_FRect texWorldRect = camera->worldToViewport_rect(showRect, texShowRect);

            SDL_RenderTexture(r,t.texture.get(), &texShowRect, &texWorldRect);
        }
    }
}

WorldWindow::WorldWindow(SDL_FRect& rect) : CreatorComponent(rect) {
    float border = 25;
    showRect.x += border;
    showRect.y += border;
    showRect.w -= 2 * border;
    showRect.h -= 2 * border;
    realMap = { 0,0,1920,1080 };
    camera = make_unique<CreatorCamera>(showRect);

    BaseViewport = showRect;


    ResourceManager& resource = ResourceManager::Instance();
    auto tex = resource.getTexture("bk", "bk_3.jpg");
    textures.push_back({tex ,{0.0f,0.0f,(float)tex->w,(float)tex->h} });
}