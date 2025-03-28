#include "pch.h"
#include "gameObject/gameObject.h"
#include "galaxy_fighter/objects/MainMenuObject/MenuImage.h"

enum game_name {
	galaxy_fighter,
	mind_clear,
	monster_hunter,
	none_selected
};
class Menu {
public:
	Menu();
	~Menu();
	void welcome();
	void startGame();
	void startMapCreator();
private:
	void init();
	void loadResource();
	void destroy();
	void update();
	bool running;

	game_name selectGame();
	void game_clean(GameObject** game);
	GameObject* playing_game;
	vector<unique_ptr<MenuButton>> logoList;
	//vector<unique_ptr<MainMenuObject>> textList;
	unique_ptr<MenuBackground> bk;
};