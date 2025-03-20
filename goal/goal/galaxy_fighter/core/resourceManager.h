#pragma once
#include <graphics.h>
#include <vector>
#include <SDL3/SDL.h>
#include "../objects/playerObject/SpritePlayer.h"

using namespace std;

using texturePtr = std::shared_ptr<SDL_Texture>;
using fontPtr = std::unique_ptr<TTF_Font, function<void(TTF_Font*)>>;

enum TTF_Type {
	PingFang,
	Pixel_10,
	Pixel_12

};


class ResourceManager {
public:
	static ResourceManager& Instance();



	shared_ptr<SDL_Texture> getTexture(const string& catelog,const string& textureName);
	TTF_Font* getFont(const string& type, int size);


	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
private:
	ResourceManager();
	~ResourceManager();

	string basePath_texture;
	string basePath_font;
	string basePath_music;

	unordered_map<string, texturePtr> textureManager;
	unordered_map<string,unordered_map<int,fontPtr>> fonts;





	//Í¼Æ¬
	SDL_Renderer* renderer;
	//×ÖÌå

	
	//¾«Áé
	vector<texturePtr> spriteSheet_player;
};
