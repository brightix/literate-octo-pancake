#pragma once
#include "pch.h"
#include "WorldWindow.h"
#include "ToolsWindow.h"
#include "AssetsWindow.h"

extern int CheckBoxIdAdder;

/*


class ResizeCheckBox_bottom {
	bool isResizing = false;
	int checkBoxId;
	bool isVertical;
public:
	ResizeCheckBox_bottom() {
		checkBoxId = CheckBoxIdAdder++;
	}

	SDL_FRect checkBox;
	float borderThickness = 5;
	std::vector<CreatorComponent*> left;
	std::vector<CreatorComponent*> right;
	std::vector<CreatorComponent*> top;
	std::vector<CreatorComponent*> bottom;

	int checkStretch_ver() {
		CreatorDebug debug;
		InputManager& input = InputManager::Instance();
		static float LeftW;
		static float OriginX;
		static float RightX;
		static float RightW;
		  // 记录正在调整的 checkBoxId

		auto [x, y] = input.getMousexy();

		if (input.isCursorHovering(&checkBox) || resizingCheckBoxId == checkBoxId) {
			debug.printText<float>("resize", checkBoxId, { (float)x,(float)y });
			SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_EW_RESIZE));

			if (input.isMouseButtonPressed(SDL_BUTTON_LEFT)) {
				if (resizingCheckBoxId == -1) {  // 确保只有一个 checkBox 进入拖拽状态
					resizingCheckBoxId = checkBoxId;
					isResizing = true;
					OriginX = x;
					RightX = right[0]->GetPlaceholderRect().x;
					LeftW = left[0]->GetPlaceholderRect().w;
					RightW = right[0]->GetPlaceholderRect().w;
				}

				if (resizingCheckBoxId == checkBoxId) {  // 仅调整正在拖拽的 checkBox
					float deltaX = x - OriginX;
					debug.printText<float>("deltaX", deltaX, { (float)x,(float)y });
					float lpw = LeftW + deltaX;
					float rx = RightX + deltaX;
					float rpw = RightW - deltaX;

					if (lpw < 100 || rpw < 100) return checkBoxId;

					for (auto component : left) {
						component->SetPlaceholderRectW(lpw);
					}
					for (auto component : right) {
						component->SetPlaceholderRectX(rx);
						component->SetPlaceholderRectW(rpw);
					}
					checkBox.x = right[0]->GetPlaceholderRect().x - borderThickness / 2;
				}
			}
			else if (isResizing && resizingCheckBoxId == checkBoxId) {
				SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT));
				isResizing = false;
				resizingCheckBoxId = -1;  // 释放拖拽
			}
			return checkBoxId;
		}
		else {
			SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT));
		}
		return -1;
	}
	
};

class ResizeCheckBox_hor {
	bool isResizing = false;
	int checkBoxId;
	bool isVertical;
public:
	ResizeCheckBox_hor() {
		checkBoxId = CheckBoxIdAdder++;
	}
	SDL_FRect checkBox;
	float borderThickness = 5;
	std::vector<CreatorComponent*> top;
	std::vector<CreatorComponent*> bottom;
	int checkStretch_hor() {
		CreatorDebug debug;
		InputManager& input = InputManager::Instance();
		static float LeftW;
		static float OriginX;
		static float RightX;
		static float RightW;

		auto [x, y] = input.getMousexy();

		if (input.isCursorHovering(&checkBox) || resizingCheckBoxId == checkBoxId) {
			debug.printText<float>("resize", checkBoxId, { (float)x,(float)y });
			SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NS_RESIZE));

			if (input.isMouseButtonPressed(SDL_BUTTON_LEFT)) {
				if (resizingCheckBoxId == -1) {  // 确保只有一个 checkBox 进入拖拽状态
					resizingCheckBoxId = checkBoxId;
					isResizing = true;
					OriginX = x;
					RightX = bottom[0]->GetPlaceholderRect().y;
					LeftW = top[0]->GetPlaceholderRect().h;
					RightW = bottom[0]->GetPlaceholderRect().h;
				}

				if (resizingCheckBoxId == checkBoxId) {  // 仅调整正在拖拽的 checkBox
					float deltaX = y - OriginX;
					debug.printText<float>("deltaX", deltaX, { (float)x,(float)y });
					float lpw = LeftW + deltaX;
					float rx = RightX + deltaX;
					float rpw = RightW - deltaX;

					if (lpw < 100 || rpw < 100) return checkBoxId;

					for (auto component : top) {
						component->SetPlaceholderRectH(lpw);
					}
					for (auto component : bottom) {
						component->SetPlaceholderRectY(rx);
						component->SetPlaceholderRectH(rpw);
					}
					checkBox.y = bottom[0]->GetPlaceholderRect().y - borderThickness / 2;
				}
			}
			else if (isResizing && resizingCheckBoxId == checkBoxId) {
				SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT));
				isResizing = false;
				resizingCheckBoxId = -1;  // 释放拖拽
			}
			return checkBoxId;
		}
		else {
			SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT));
		}
		return -1;
	}
};
*/





class MapCreator :
	public CreatorComponent
{
	WorldWindow* worldWindow;
	ToolsWindow* toolsWindow;
	AssetsWindow* assetsWindow;
	bool isResizing = false;
	float initialResizingX;
	std::vector<CreatorComponent*> components;
	DefaultComponent* defaultComponent;

public:
	MapCreator();
	MapCreator(SDL_FRect rect);
	~MapCreator();

	void Update();
private:
	void CheckResizing();
	void init();
};













/*
enum InsertMethod{
	TopInsert = 0,
	BottomInsert,
	LeftInsert,
	RightInsert
};


static SDL_Cursor* cursorEW = nullptr;
static SDL_Cursor* cursorNS = nullptr;
static SDL_Cursor* cursorDefault = nullptr;
static int resizingCheckBoxId = -1;

class ResizeCheckBox {
protected:
	bool isResizing = false;
	int checkBoxId;
public:
	SDL_FRect checkBox;
	float borderThickness = 5;
	ResizeCheckBox(){
		checkBoxId = CheckBoxIdAdder++;

		if (!cursorEW) cursorEW = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_EW_RESIZE);
		if (!cursorNS) cursorNS = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NS_RESIZE);
		if (!cursorDefault) cursorDefault = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
	}
	virtual int checkStretch(int id ,float mouseX,float mouseY ,bool hovering, bool isClicked) = 0;
};
	static float originX;
	static float leftW;
	static float rightX;
	static float rightW;
class ResizeCheckBox_hor :
	public ResizeCheckBox
{

	CreatorComponent* left;
	CreatorComponent* right;
public:
	int checkStretch(int id, float mouseX, float mouseY, bool hovering, bool isClicked) {
		if (hovering) {
			SDL_SetCursor(cursorEW);
			if (isClicked) {
				if (!isResizing) {
					originX = mouseX;
					leftW = left->GetPlaceholderRect().w;
					rightX = right->GetPlaceholderRect().x;
					rightW = right->GetPlaceholderRect().w;
				}
				float deltaX = mouseX - rightX;

				left->SetPlaceholderRectW(leftW + deltaX);
				right->SetPlaceholderRectX(rightX + deltaX);
				right->SetPlaceholderRectW(rightW + deltaX);
			}
			else if (isResizing) {
				SDL_SetCursor(cursorDefault);
				return -1;
			}
			return checkBoxId;
		}
		else {
			SDL_SetCursor(cursorDefault);
		}
		return -1;
	}
};

	static float originY;
	static float topH;
	static float bottomY;
	static float bottomH;
class ResizeCheckBox_left :
	public ResizeCheckBox
{

	CreatorComponent* left;
	CreatorComponent* right;
	std::vector<CreatorComponent*>& components;
public:
	ResizeCheckBox_left(std::vector<CreatorComponent*>& components) : components(components) {}
	int checkStretch(int id, float mouseX, float mouseY, bool hovering, bool isClicked) {
		if (hovering) {
			SDL_SetCursor(cursorNS);
			if (isClicked) {
				if (!isResizing) {
					originX = mouseX;
					leftW = left->GetPlaceholderRect().w;
					rightX = right->GetPlaceholderRect().x;
					rightW = right->GetPlaceholderRect().w;
				}
				float deltaX = mouseX - rightX;

				left->SetPlaceholderRectW(leftW + deltaX);
				right->SetPlaceholderRectX(rightX + deltaX);
				right->SetPlaceholderRectW(rightW + deltaX);
			}
			else if (isResizing) {
				SDL_SetCursor(cursorDefault);
				return -1;
			}
			return checkBoxId;
		}
		else {
			SDL_SetCursor(cursorDefault);
		}
		return -1;
	}

};

class ResizeCheckBox_bottom : public ResizeCheckBox{
	CreatorComponent* top;
	CreatorComponent* bottom;
	std::vector<CreatorComponent*>& components;
public:
	ResizeCheckBox_bottom(std::vector<CreatorComponent*>& components) : components(components) {}
	int checkStretch(int id, float mouseX, float mouseY, bool hovering, bool isClicked) {
		if (hovering) {
			SDL_SetCursor(cursorEW);
			if (isClicked) {
				if (!isResizing) {
					originY = mouseX;
					topH = top->GetPlaceholderRect().h;
					bottomY = bottom->GetPlaceholderRect().y;
					bottomH = bottom->GetPlaceholderRect().h;
				}
				float deltaY = mouseY - topH;

				float topNewH = topH + deltaY;
				float bottomNewY = bottomY + deltaY;
				float bottomNewH = bottomH + deltaY;

				float bottomY = bottom->GetContentRect().y;
				for (auto component : components) {
					auto crect = component->GetPlaceholderRect();
					if (crect.y + crect.h == bottomY) {
						component->SetPlaceholderRectH(topNewH);
					}
				}
				bottom->SetPlaceholderRectY(bottomNewY);
				bottom->SetPlaceholderRectH(bottomNewH);
			}
			else if (isResizing) {
				SDL_SetCursor(cursorDefault);
				return -1;
			}
			return checkBoxId;
		}
		else {
			SDL_SetCursor(cursorDefault);
		}
		return -1;
	}
};

class UIManager {
	std::vector<CreatorComponent*>& components;
public:
	UIManager(std::vector<CreatorComponent*>& components) : components(components) {

	}
	ResizeCheckBox* Insert_hor(CreatorComponent* origin, CreatorComponent* split, const bool isLeft) {
		const SDL_FRect& originRect = origin->GetPlaceholderRect();
		if (origin->GetUIName() == 0) {
			SDL_FRect rect = originRect;
			split->SetPlaceholderRect(rect);
			return nullptr;
		}

		float distance;
		SDL_FRect firstDiv = originRect;
		SDL_FRect secondDiv = originRect;
		ResizeCheckBox*res = new ResizeCheckBox_hor();
		distance = originRect.w / 2;
		firstDiv.w = distance;
		secondDiv.x = firstDiv.x + firstDiv.w;
		secondDiv.w = originRect.w - firstDiv.w;
		res->checkBox = firstDiv;
		res->checkBox.x = secondDiv.x - res->borderThickness / 2;
		res->checkBox.w = 2 * res->borderThickness;

		if (isLeft) {
			origin->SetPlaceholderRect(secondDiv);
			split->SetPlaceholderRect(firstDiv);
		}
		else {
			origin->SetPlaceholderRect(firstDiv);
			split->SetPlaceholderRect(secondDiv);
		}
		return res;
	}
	ResizeCheckBox* Set_bottom(CreatorComponent* origin, CreatorComponent* split) {
		const SDL_FRect& originRect = origin->GetPlaceholderRect();
		float distance;
		SDL_FRect firstDiv = originRect;
		SDL_FRect secondDiv = originRect;

		ResizeCheckBox* res = nullptr;

		/* 底部插入
		res = new ResizeCheckBox_bottom(components);
		distance = originRect.h / 3;
		firstDiv.h = distance;
		secondDiv.y = firstDiv.y + firstDiv.h;
		secondDiv.h = originRect.h - firstDiv.h;
		res->checkBox = firstDiv;
		res->checkBox.y = secondDiv.y - res->borderThickness / 2;
		res->checkBox.h = 2 * res->borderThickness;

		origin->SetPlaceholderRect(secondDiv);
		split->SetPlaceholderRect(firstDiv);
		return res;
	}
	ResizeCheckBox* Set_left(CreatorComponent* origin, CreatorComponent* split) {
		const SDL_FRect& originRect = origin->GetPlaceholderRect();
		float distance;
		float distance;
		SDL_FRect firstDiv = originRect;
		SDL_FRect secondDiv = originRect;
		ResizeCheckBox* res = new ResizeCheckBox_left(components);
		distance = originRect.w / 5;
		firstDiv.w = distance;
		secondDiv.x = firstDiv.x + firstDiv.w;
		secondDiv.w = originRect.w - firstDiv.w;
		res->checkBox = firstDiv;
		res->checkBox.x = secondDiv.x - res->borderThickness / 2;
		res->checkBox.w = 2 * res->borderThickness;

		origin->SetPlaceholderRect(secondDiv);
		split->SetPlaceholderRect(firstDiv);

		return res;
		return res;
	}
};
*/
