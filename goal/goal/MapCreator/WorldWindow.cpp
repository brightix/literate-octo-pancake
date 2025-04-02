#include "pch.h"
#include "WorldWindow.h"
#include "../galaxy_fighter/utils/Math.h"



void WorldWindow::Update()
{
    UpdateInput();
    UpdateAttr();
    scaleFactor = windowShowRect.w / camera->GetViewport().w;
	DrawBackground();

    DrawSubLine();
    DrawTexture();
    DrawInfo();
}

void WorldWindow::UpdateAttr() {
    auto& viewport = camera->GetViewport();
    BaseViewport.w = BaseViewport.h * (viewport.w / viewport.h);
}

void WorldWindow::UpdateInput() {
    InputManager& input = InputManager::Instance();
    if (input.isCursorHovering(&windowShowRect) || relativeMouseMode) {
        /* ÖÐ¼üÍÏ¶¯ÆÁÄ» */
        if (input.isMouseButtonPressed(SDL_BUTTON_MIDDLE)) {
            input.setRelativeMouseMode(relativeMouseMode);
            auto [x,y] = input.getRelativeMousexy();
            if (!relativeMouseMode) {
                relativeMouseMode = true;
                return;
            }

            camera->addViewportXY(-x * 2 * windowAreaScale,-y * 2 * windowAreaScale);
        }
        else if (relativeMouseMode) {
            relativeMouseMode = false;
            input.setRelativeMouseMode(relativeMouseMode);
        }
        else if (int dir = input.isMouseWheelYScrolled()) {
            /* ¹öÂÖËõ·Å */
            if (dir < 0) {
                windowAreaScale = min(windowAreaScale * 1.1f, 100.0f);
            }
            else {
                windowAreaScale = max(windowAreaScale / 1.1f, 0.01f);
            }


            auto [x, y] = input.getMousexy();
            SDL_FPoint XY = {x,y};

            SDL_FPoint prevMouseOnWorld = camera->ScreenToWorld_dot(windowShowRect,XY);
            camera->setViewportWH(BaseViewport.w * windowAreaScale,BaseViewport.h * windowAreaScale);

            SDL_FPoint afterMouseOnWorld = camera->ScreenToWorld_dot(windowShowRect, XY);
            camera->addViewportXY(prevMouseOnWorld.x - afterMouseOnWorld.x, prevMouseOnWorld.y - afterMouseOnWorld.y);
        }
    }

    if (input.isKeyPressed(SDL_SCANCODE_D)) {
        camera->addViewportXY(10 * windowAreaScale, 0);
    }
    if (input.isKeyPressed(SDL_SCANCODE_A)) {
        camera->addViewportXY(-10 * windowAreaScale, 0);
    }
    if (input.isKeyPressed(SDL_SCANCODE_S)) {
        camera->addViewportXY(0, 10 * windowAreaScale);
    }
    if (input.isKeyPressed(SDL_SCANCODE_W)) {
        camera->addViewportXY(0,-10 * windowAreaScale);
    }
}

void WorldWindow::DrawSubLine() {
    auto& textRenderer = TextRenderer::Instance();
    auto color = ColorManager::Instance().getColor(SubLineColor);
    SDL_SetRenderDrawBlendMode(r,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);

    float gap;
    if (windowAreaScale < 1.0f) {
        gap = 100.0f;
    }
    else if (windowAreaScale < 5.0f) {
        gap = 500.f;
    }
    else if (windowAreaScale < 10.0f) {
        gap = 1000.f;
    }
    else if (windowAreaScale < 15.0f) {
        gap = 1500.f;
    }
    else {
        gap = 2000.0f;
    }
    SDL_FRect viewport = camera->GetViewport();
    float i = ceil(viewport.x / gap) * gap;
    float j = viewport.y + viewport.h;
    float n = floor((viewport.x + viewport.w) / gap) * gap;
    int textSize = 10;
    for (i;i <= n;i += gap) {
        SDL_FPoint p1 = camera->WorldToViewport_dot(windowShowRect, { i,viewport.y });
        SDL_FPoint p2 = camera->WorldToViewport_dot(windowShowRect, { i,j });
        SDL_RenderLine(r, p1.x, p1.y, p2.x, p2.y);

        SDL_FPoint index = camera->WorldToViewport_dot(windowShowRect, { i,viewport.y });
        textRenderer.renderText(index.x, index.y, textRenderer.getTextTexture(to_string(static_cast<int>(i)), "pingfang", 10).get());
    }
    
    i = ceil(viewport.y / gap) * gap;
    j = viewport.x + viewport.w;
    n = floor((viewport.y + viewport.h) / gap) * gap;
    for (i;i <= n;i += gap) {
        SDL_FPoint p1 = camera->WorldToViewport_dot(windowShowRect, { viewport.x,i });
        SDL_FPoint p2 = camera->WorldToViewport_dot(windowShowRect, { j,i });
        SDL_RenderLine(r, p1.x, p1.y, p2.x, p2.y);

        SDL_FPoint index = camera->WorldToViewport_dot(windowShowRect, { viewport.x,i });
        textRenderer.renderText(index.x, index.y, textRenderer.getTextTexture(to_string(static_cast<int>(i)), "pingfang", 10).get());
    }
}

void WorldWindow::DrawInfo() {
    CreatorDebug debug;
    auto& textRenderer = TextRenderer::Instance();
    SDL_FPoint p = { windowShowRect.x,windowShowRect.y };

    debug.printText("scaleFactor",to_string(scaleFactor), p);
    SDL_FRect viewport = camera->GetViewport();
    debug.printText("viewportRatio", to_string(viewport.w / viewport.h), {p.x,p.y+20});
    debug.printText("windowShowRatio", to_string(windowShowRect.w / windowShowRect.h), { p.x,p.y + 40 });
    debug.printRectInfo("placeholderRect", placeholderRect, GetPlaceholderRect(), 3);
    debug.printRectInfo("viewport",viewport, GetPlaceholderRect(),4);
    debug.printRectInfo("windowShowRect", windowShowRect, GetPlaceholderRect(),5);

}

void WorldWindow::DrawTexture() {
    for (auto t : textures) {
        if (camera->isOnScreen(t.rect)) {
            SDL_FRect texwindowShowRect = camera->transformViewportArea(t.rect);
            SDL_FRect texWorldRect = camera->WorldToViewport_rect(windowShowRect, texwindowShowRect);

            SDL_RenderTexture(r,t.texture.get(), &texwindowShowRect, &texWorldRect);
        }
    }
}

WorldWindow::WorldWindow(SDL_FRect placeholder) : CreatorComponent(placeholder){
    WindowId = WindowIdAdder++;
    name = "World";
    float border = 25;
    realMap = { 0,0,1920,1080 };
    camera = make_unique<CreatorCamera>(windowShowRect);
    camera->setCameraRange(nullptr);
    BaseViewport = realMap;


    ResourceManager& resource = ResourceManager::Instance();
    auto tex = resource.getTexture("bk", "bk_3.jpg");
    //textures.push_back({tex ,{0.0f,0.0f,(float)tex->w,(float)tex->h} });
}