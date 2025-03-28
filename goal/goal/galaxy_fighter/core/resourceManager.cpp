#include "pch.h"
#include <SDL3_image/SDL_image.h>
#include "ResourceManager.h"

namespace fs = std::filesystem;

ResourceManager& ResourceManager::Instance() {
	static ResourceManager instance;
	return instance;
}

shared_ptr<SDL_Texture> ResourceManager::getTexture(const string& catalog, const string& textureName)
{
	string name = catalog + textureName;
	string path = basePath_texture + "\\" + catalog + "\\" + textureName;
	if (textureManager.find(name) == textureManager.end()) {
		SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
		if (!texture) {
			cout << "��ͼ���ش���û�е�ַΪ " << path << " ��ͼƬ" << endl;
			return nullptr;
		}
		textureManager[name] = shared_ptr<SDL_Texture>(texture, SDL_DestroyTexture);
	}
	return textureManager[name];
}

TTF_Font* ResourceManager::getFont(const std::string& type, int size) {
	// ȷ�� `type` ����
	auto& size_map = fonts[type];

	// �����Ƿ��Ѿ������˸ô�С������
	auto it = size_map.find(size);
	if (it != size_map.end()) {
		return it->second.get(); // ֱ�ӷ��ػ�������
	}

	// ����������
	std::string fontPath = basePath_font + "\\" + type + ".ttf";
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), size);

	// ȷ��������سɹ�
	if (!font) {
		std::cerr << "Failed to load font" << std::endl;
		return nullptr;
	}

	// �洢�� `fonts` ӳ��
	size_map[size] = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>(font, TTF_CloseFont);

	return font;
}

ResourceManager::ResourceManager() {
	this->renderer = RendererManager::Instance().getRenderer();
	fs::path currentPath = fs::current_path();
	basePath_texture = (currentPath / "galaxy_fighter" / "assets" / "img").string();
	basePath_font = (currentPath / "galaxy_fighter" / "assets" / "font").string();
	basePath_music = (currentPath / "galaxy_fighter" / "assets" / "music").string();
	cout << currentPath << endl;
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




ResourceManager::~ResourceManager(){
	cout << "��Դ���������������ѹر�" << endl;
}
