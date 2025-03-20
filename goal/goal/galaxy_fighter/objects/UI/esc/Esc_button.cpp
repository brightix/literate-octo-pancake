#include "pch.h"
#include "Esc_button.h"
#include "../component.h"
#include "../UIManager/UIManager.h"
#include "../../../BehaviorTree/BTAction_scene/BTAction_image.h"

Esc_button::Esc_button(){
	Resolution& res = Resolution::Instance();
	float resFactor = res.getScaleFactor();
	SDL_FRect trect = {50*resFactor,50*resFactor,100*resFactor,100*resFactor};
	renderRect = make_shared<SDL_FRect>(trect);
	texture = ResourceManager::Instance().getTexture("gameLogo","logo_3.jpg").get();
	is_clicked = false;
	root = make_shared<ParalleNode>();
	root->addChild(make_shared<BTAction_image::scaling_up_hovering>(*renderRect,1.2,100,is_selected));
}

void Esc_button::render() {
	SDL_RenderTexture(RendererManager::Instance().getRenderer(),texture,nullptr,renderRect.get());
}

void Esc_button::update()
{
	InputManager& input = InputManager::Instance();
	UIManager& uiManager = UIManager::Instance();

	if (uiManager.isUiStackEmpty() && input.isCursorHovering(this->renderRect.get())) {//Ñ¡ÖÐ
		is_selected = true;

		if (input.isMouseButtonPressed(SDL_BUTTON_LEFT)) {//µã»÷
			//uiManager.pushUI(new Esc_interface());
			is_clicked = true;
		}
	}
	else {
		is_selected = false;
	}
	root->execute();
	render();
}
