#pragma once
class Camera
{
public:
	static Camera& Instance();
	SDL_FRect* getViewport();


	void setCameraOwner(BaseObject* owner);//设置跟随目标

	void setCameraRange(SDL_FRect* rect);//将地图矩形传过来
	SDL_FRect& getCameraRange();

	std::pair<bool, bool>& ownerxyCrashedState();

	void update();


	void clampToWorldBounds();
	bool isOnScreen(SDL_FRect& rect);
	SDL_FRect worldToScreen(SDL_FRect& rect);
	Camera(const Camera&) = delete;
	Camera operator=(const Camera&) = delete;
	
private:

	Camera();
	~Camera() = default;
	std::pair<bool, bool> isxyCrashed;
	BaseObject* owner;
	SDL_FRect viewport;
	SDL_FRect windowRect;
	SDL_FRect* world;
};

