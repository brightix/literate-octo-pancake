#pragma once
class Camera
{
public:
	static Camera& getInstance();
	SDL_FRect* getViewport();
	SDL_FRect* getWindowRect();
	void setCameraOwner(BaseObject* owner);//���ø���Ŀ��

	void setCameraRange(SDL_Texture* texture);//����ͼ���δ�����
	std::pair<float, float> getCameraRange();

	std::pair<bool, bool>& ownerxyCrashedState();

	void update();


	void clampToWorldBounds();
	Camera(const Camera&) = delete;
	Camera operator=(const Camera&) = delete;
	
private:

	Camera();
	~Camera() = default;
	std::pair<bool, bool> isxyCrashed;
	BaseObject* owner;
	SDL_FRect viewport;
	SDL_FRect windowRect;
	float world_width, world_height;
	int screen_width, screen_height;
};

