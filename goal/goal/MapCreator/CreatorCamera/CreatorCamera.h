#pragma once
class CreatorCamera
{
public:
	CreatorCamera() = default;
	~CreatorCamera() = default;
	CreatorCamera(SDL_FRect viewport);

	const SDL_FRect& GetViewport();

	void setCameraRange(SDL_FRect* rect);
	void setViewportXY(float x, float y);
	void setViewportWH(float w, float h);
	void addViewportXY(float x, float y);
	void addViewportWH(float w, float h);


	const SDL_FRect& getCameraRange();

	bool isOnScreen(SDL_FRect& worldRect);

	SDL_FRect WorldToViewport_rect(SDL_FRect& relativeRect, SDL_FRect rect);
	SDL_FRect WorldToViewport_line(SDL_FRect& relativeRect, SDL_FRect line);
	SDL_FPoint WorldToViewport_dot(SDL_FRect& relativeRect, SDL_FPoint p);
	SDL_FRect ScreenToWorld_rect(SDL_FRect& dstRect, SDL_FRect rect);
	SDL_FPoint ScreenToWorld_dot(SDL_FRect& dstRect, SDL_FPoint);
	SDL_FRect transformViewportArea(SDL_FRect worldRect);
private:


	std::pair<bool, bool> isxyCrashed;
	SDL_FRect viewport;
	SDL_FRect* world;
};

