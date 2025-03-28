#pragma once


class component
{
public:
	component() = default;
	SDL_FRect* getRect();
	virtual bool update() = 0;
	virtual void render() = 0;
protected:
	shared_ptr<SDL_FRect> renderRect;
};

