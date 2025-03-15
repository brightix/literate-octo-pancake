#include "pch.h"
#include "QuadTree.h"

QuadTreeNode::QuadTreeNode(SDL_FRect boundary) : boundary(boundary)
{
	std::fill(std::begin(children),std::end(children), nullptr);
}

void QuadTreeNode::inset(BaseObject& obj) {
	//if (!isWithinBoundary(obj)) return;
	//if (objects.size() > MAX_OBJECTS && currentDepth < MAX_DEPTH) {
	//	subdivide();
	//}
	//if (children[0]) {

	//}
}

bool QuadTreeNode::isWithinBoundary(BaseObject& obj) {
	return SDL_HasRectIntersectionFloat(&boundary,obj.getRect());
}

void QuadTreeNode::subdivide() {
	//float halfWidth = boundary.w / 2;
	//float halfHeight = boundary.h / 2;
	//children[0] = new QuadTreeNode({ boundary.x,boundary.y,halfWidth,halfHeight });
	//children[1] = new QuadTreeNode({ boundary.x + halfWidth,boundary.y,halfWidth,halfHeight });
	//children[2] = new QuadTreeNode({ boundary.x,boundary.y+halfHeight,halfWidth,halfHeight });
	//children[3] = new QuadTreeNode({ boundary.x+halfWidth,boundary.y+halfHeight,halfWidth,halfHeight });
}
