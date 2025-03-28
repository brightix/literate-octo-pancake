#pragma once
class CreatorCamera
{
public:
	CreatorCamera() = default;
	~CreatorCamera() = default;
	CreatorCamera(SDL_FRect viewport);
	SDL_FRect getViewport();

	void setCameraRange(SDL_FRect* rect);
	void setViewport(float x, float y);

	void addViewport(float x, float y);


	SDL_FRect& getCameraRange();

	bool isOnScreen(SDL_FRect& showRect,SDL_FRect& rect);

	SDL_FRect worldToViewport_rect(SDL_FRect& relativeRect, SDL_FRect rect);

	SDL_FRect worldToViewport_line(SDL_FRect& relativeRect, SDL_FRect line);

	SDL_FPoint worldToViewport_dot(SDL_FRect& relativeRect, SDL_FPoint p);
	SDL_FRect transformViewportArea(SDL_FRect worldRect);
private:


	std::pair<bool, bool> isxyCrashed;
	SDL_FRect viewport;
	SDL_FRect* world;
};

