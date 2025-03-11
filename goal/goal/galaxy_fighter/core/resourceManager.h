#pragma once
#include <graphics.h>
#include <vector>
#include <SDL3/SDL.h>
#include "../objects/playerObject/SpritePlayer.h"

using namespace std;

using texturePtr = std::unique_ptr<SDL_Texture, function<void(SDL_Texture*)>>;
using fontPtr = std::unique_ptr<TTF_Font, function<void(TTF_Font*)>>;

enum TTF_Type {
	PingFang,
	Pixel_10,
	Pixel_12

};


class ResourceManager {
public:
	static ResourceManager& getInstance();





	//图片类
	SDL_Texture* getDefault();
	SDL_Texture* getPromptBoxImage();

	vector<texturePtr>& get_hero();
	vector<texturePtr>& get_hero_destroy();
	vector<texturePtr>& get_bk();
	vector<texturePtr>& get_enemy();
	vector<texturePtr>& get_enemy_destroy();
	vector<texturePtr>& get_hero_bullet();
	vector<texturePtr>& get_hero_bullet_destroy();
	vector<texturePtr>& get_enemy_bullet();
	vector<texturePtr>& get_enemy_bullet_destroy();
	vector<texturePtr>& getPilot();
	vector<texturePtr>& get_game_logo();

	//字体类
	TTF_Font* get_font(const string& type, int size);

	//精灵
	vector<texturePtr>& get_sprite_sheet_player();

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
private:
	ResourceManager();
	~ResourceManager();
	//图片
	SDL_Renderer* renderer;
	texturePtr defaultImage;
	texturePtr promptBoxImage;

	vector<texturePtr> pilot;

	vector<texturePtr> hero;
	vector<texturePtr> hero_destroy;
	vector<texturePtr> hero_bullet;
	vector<texturePtr> hero_bullet_destroy;

	vector<texturePtr> enemy;
	vector<texturePtr> enemy_destroy;

	vector<texturePtr> enemy_bullet;
	vector<texturePtr> enemy_bullet_destroy;

	vector<texturePtr> bk;
	vector<texturePtr> game_logo;
	//字体
	unordered_map<string,unordered_map<int,fontPtr>> fonts;
	
	//精灵
	vector<texturePtr> spriteSheet_player;
};
