#include "pch.h"
#include "UIManager.h"

UIManager& UIManager::Instance() { static UIManager instance; return instance; }

void UIManager::pushUI(component* ui) {
	uiStack.emplace_back(ui);
}

void UIManager::popUI()
{
	uiStack.pop_back();
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
	uiStack[uiStack.size() - 1]->update();
}
