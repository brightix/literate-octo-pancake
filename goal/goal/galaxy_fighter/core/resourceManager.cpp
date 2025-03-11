#include "pch.h"
#include <SDL3_image/SDL_image.h>
#include "ResourceManager.h"

namespace fs = std::filesystem;

ResourceManager& ResourceManager::getInstance() {
	static ResourceManager instance;
	return instance;
}

extern void loadTexture_vector_ptr(vector<texturePtr>& vt, string path, SDL_Renderer* renderer);

ResourceManager::ResourceManager() {
	renderer = RendererManager::getInstance().getRenderer();

	loadTexture_vector_ptr(hero, ".\\galaxy_fighter\\assets\\img\\player\\normal",renderer);
	loadTexture_vector_ptr(hero_destroy, ".\\galaxy_fighter\\assets\\img\\player\\destroy", renderer);

	loadTexture_vector_ptr(hero_bullet, ".\\galaxy_fighter\\assets\\img\\bullet\\hero_bullet\\normal", renderer);
	loadTexture_vector_ptr(hero_bullet_destroy, ".\\galaxy_fighter\\assets\\img\\bullet\\hero_bullet\\destroy", renderer);
	loadTexture_vector_ptr(enemy, ".\\galaxy_fighter\\assets\\img\\enemy\\normal", renderer);
	loadTexture_vector_ptr(enemy_destroy, ".\\galaxy_fighter\\assets\\img\\enemy\\destroy", renderer);

	loadTexture_vector_ptr(enemy_bullet, ".\\galaxy_fighter\\assets\\img\\bullet\\enemy_bullet\\normal", renderer);
	loadTexture_vector_ptr(enemy_bullet_destroy, ".\\galaxy_fighter\\assets\\img\\bullet\\hero_bullet\\destroy", renderer);

	loadTexture_vector_ptr(bk, ".\\galaxy_fighter\\assets\\img\\bk", renderer);
	loadTexture_vector_ptr(game_logo, ".\\galaxy_fighter\\assets\\img\\gameLogo", renderer);
	loadTexture_vector_ptr(spriteSheet_player, ".\\galaxy_fighter\\assets\\img\\player\\spriteSheet",renderer);
}


void loadTexture_vector_ptr(vector<texturePtr>& vt, string path,SDL_Renderer* renderer) {
	std::vector<fs::path> fphs;
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.is_regular_file() && (entry.path().extension() == ".png" || entry.path().extension() == ".jpg")) {
			fphs.push_back(entry.path());
		}
	}
	sort(fphs.begin(), fphs.end());
	for (auto& fph : fphs) {
		SDL_Texture* texture = IMG_LoadTexture(renderer,fph.string().c_str());
		if (!texture) {
			cerr << "Texture load failed: " << SDL_GetError() << std::endl;
			continue;
		}
		vt.emplace_back(std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>(texture,SDL_DestroyTexture));
	}
}






SDL_Texture* ResourceManager::getDefault() { return defaultImage.get(); }
SDL_Texture* ResourceManager::getPromptBoxImage() { return promptBoxImage.get(); }
vector<texturePtr>& ResourceManager::get_hero() { return hero; }
vector<texturePtr>& ResourceManager::get_hero_destroy() { return hero_destroy; }

vector<texturePtr>& ResourceManager::get_bk() { return bk; }
vector<texturePtr>& ResourceManager::get_enemy() { return enemy; }
vector<texturePtr>& ResourceManager::get_enemy_destroy() { return enemy_destroy; }
vector<texturePtr>& ResourceManager::get_hero_bullet() { return hero_bullet; }
vector<texturePtr>& ResourceManager::get_hero_bullet_destroy() { return hero_bullet_destroy; }

vector<texturePtr>& ResourceManager::get_enemy_bullet() { return enemy_bullet; }
vector<texturePtr>& ResourceManager::get_enemy_bullet_destroy() { return enemy_bullet_destroy; }
vector<texturePtr>& ResourceManager::getPilot() { return pilot; }

vector<texturePtr>& ResourceManager::get_game_logo() { return game_logo; }
vector<texturePtr>& ResourceManager::get_sprite_sheet_player() { return spriteSheet_player; }


TTF_Font* ResourceManager::get_font(const std::string& type, int size) {
	// 确保 `type` 存在
	auto& size_map = fonts[type];

	// 查找是否已经加载了该大小的字体
	auto it = size_map.find(size);
	if (it != size_map.end()) {
		return it->second.get(); // 直接返回缓存字体
	}

	// 加载新字体
	std::string fontPath = ".\\galaxy_fighter\\assets\\font\\" + type + ".ttf";
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), size);

	// 确保字体加载成功
	if (!font) {
		std::cerr << "Failed to load font" << std::endl;
		return nullptr;
	}

	// 存储到 `fonts` 映射
	size_map[size] = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>(font, TTF_CloseFont);

	return font;
}

ResourceManager::~ResourceManager(){
	cout << "资源管理器单例单例已关闭" << endl;
}
