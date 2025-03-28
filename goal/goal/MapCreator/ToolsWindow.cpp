#include "pch.h"
#include "ToolsWindow.h"

void ToolsWindow::Update()
{
	DrawBackground();
	DrawSubBorder(placeholderRect);
	DrawSubBorder(showRect);
}
