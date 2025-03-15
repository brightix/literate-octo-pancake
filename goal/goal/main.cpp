#include "menu.h"

int main() {
	// 设置控制台输出为 UTF-8
	SetConsoleOutputCP(CP_UTF8);
	// 设置控制台输入为 UTF-8
	SetConsoleCP(CP_UTF8);

	Menu menu;
	//menu.welcome();
	menu.startGame();
	return 0;
}