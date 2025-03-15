#include "pch.h"
#include "QuadTree.h"

QuadTree::QuadTree(Rect boundary) : boundary(boundary)
{
	std::fill(std::begin(children),std::end(children), nullptr);
}

void QuadTree::inset(BaseObject& obj) {
	//if (!isWithinBoundary(obj)) return;
	//if (objects.size() > MAX_OBJECTS && currentDepth < MAX_DEPTH) {
	//	subdivide();
	//}
	//if (children[0]) {

	//}
}
//
//bool QuadTree::isWithinBoundary(BaseObject& obj) {
//	return SDL_HasRectIntersectionFloat(, obj.getRect());
//}

void QuadTree::subdivide() {
	SDL_FRect* rect = boundary.rect.get();
	float halfWidth = rect->w / 2;
	float halfHeight = rect->h / 2;

	auto r1 = std::make_shared<SDL_FRect>(SDL_FRect{ rect->x, rect->y, halfWidth, halfHeight });
	children[0] = std::make_unique<QuadTree>(Rect(r1));

	// 子区域 2 (右上)
	auto r2 = std::make_shared<SDL_FRect>(SDL_FRect{ rect->x + halfWidth, rect->y, halfWidth, halfHeight });
	children[1] = std::make_unique<QuadTree>(Rect(r2));

	// 子区域 3 (左下)
	auto r3 = std::make_shared<SDL_FRect>(SDL_FRect{ rect->x, rect->y + halfHeight, halfWidth, halfHeight });
	children[2] = std::make_unique<QuadTree>(Rect(r3));

	// 子区域 4 (右下)
	auto r4 = std::make_shared<SDL_FRect>(SDL_FRect{ rect->x + halfWidth, rect->y + halfHeight, halfWidth, halfHeight });
	children[3] = std::make_unique<QuadTree>(Rect(r4));
}
