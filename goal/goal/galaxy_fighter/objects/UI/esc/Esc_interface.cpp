#include "pch.h"
#include "Esc_interface.h"
#include "../UIManager/UIManager.h"
#include "../../../core/TextRenderer.h"
Esc_interface::Esc_interface()
{
	backgroundColor = {67,67,67,150};
}

void Esc_interface::render()
{
	auto r = RendererManager::Instance().getRenderer();
	SDL_SetRenderDrawBlendMode(r,SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(r,backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	SDL_RenderFillRect(r,&Resolution::Instance().getWindowRect());
	//auto texture = TextRenderer::Instance().getTextTexture("你单击了确定按钮","pingfang",40);
	//SDL_FRect rect = {500,500,0,0};
	//SDL_GetTextureSize(texture.get(),&rect.w,&rect.h);
	//SDL_SetRenderDrawColor(RendererManager::Instance().getRenderer(), 255,255,255,255);
	//for (int i = 0;i < 3;i++) {
	//	rect = { rect.x + i,rect.y + i,rect.w - 2 * i,rect.h - 2 * i };
	//	SDL_RenderRect(r, &rect);
	//}

	//SDL_RenderTexture(RendererManager::Instance().getRenderer(),texture.get(), nullptr,&rect);
}

bool Esc_interface::update()
{
	auto& uimanager = UIManager::Instance();
	if (uimanager.IsQuit()) {
		return true;
	}
	return false;
}
