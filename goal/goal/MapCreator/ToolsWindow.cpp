#include "pch.h"
#include "ToolsWindow.h"


ToolsWindow::ToolsWindow(SDL_FRect placeholder) : CreatorComponent(placeholder) {
	WindowId = WindowIdAdder++;
	UpdateShowRect();
}
void ToolsWindow::Update()
{
	DrawBackground();
	DrawSubBorder(placeholderRect);
	DrawSubBorder(windowShowRect);
}
