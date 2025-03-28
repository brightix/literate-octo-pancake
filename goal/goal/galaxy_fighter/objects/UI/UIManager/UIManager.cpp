#include "pch.h"
#include "UIManager.h"

UIManager& UIManager::Instance() { static UIManager instance; return instance; }

void UIManager::pushUI(component* ui) {
	uiStack.emplace_back(ui);
}

void UIManager::popUI()
{
	delete uiStack[uiStack.size() - 1];
	uiStack.pop_back();
}

void UIManager::refreshEscButton() {
	escUIHasPushed = false;
}

void UIManager::EscUIHasPushed() {
	escUIHasPushed = true;
}

bool UIManager::isUiStackEmpty() {
	return uiStack.empty();
}



void UIManager::update() {
	if (uiStack.empty()) {
		return;
	}
	for (auto ui : uiStack) {
		ui->render();
	}
	if (uiStack[uiStack.size() - 1]->update()) {
		popUI();
	}
}

bool UIManager::IsQuit() {
	return !escUIHasPushed && InputManager::Instance().isKeyPressedOnce(SDL_SCANCODE_ESCAPE);
}
