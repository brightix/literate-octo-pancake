#include "menu.h"

int main() {
	// ���ÿ���̨���Ϊ UTF-8
	SetConsoleOutputCP(CP_UTF8);
	// ���ÿ���̨����Ϊ UTF-8
	SetConsoleCP(CP_UTF8);

	Menu menu;
	//menu.welcome();
	menu.startGame();
	return 0;
}