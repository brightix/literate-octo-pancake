#pragma once
#include "../../objects/BaseObject.h"



class Rect {
public:
	SDL_FRect rect;
	Rect() { rect = { 100,100,100,100 }; }
	Rect(SDL_FRect rect) : rect(rect) {}
	bool intersects(Rect& other) {
		SDL_FRect& otherR = other.rect;
		return !(rect.x + rect.w < otherR.x ||
			rect.x > otherR.x + otherR.w ||
			rect.y + rect.h < otherR.y ||
			rect.y > otherR.y + otherR.h);
	}

	bool contains(float px,float py) {
		return px >= rect.x && px <= rect.x + rect.w && py >= rect.y && py <= rect.y + rect.h;
	}
};

class QuadTree
{
	static constexpr int MAX_OBJECTS = 4;
	static constexpr int MAX_LEVEL = 5;
	int level;
	Rect bounds;
	std::vector<BaseObject*> objects;
	QuadTree* node[4];
public:
	QuadTree() = default;
	QuadTree(int lvl, Rect area) : level(lvl), bounds(area) {
		for (int i = 0;i < 4;i++) {
			node[i] = nullptr;
		}
	}
	~QuadTree() { clear(); }

	void clear() {
		objects.clear();
		for (int i = 0;i < 4;i++) {
			delete node[i];
			node[i] = nullptr;
		}
	}

	void subdivide() {
		float halfWidth = bounds.rect.w / 2;
		float halfHeight = bounds.rect.h / 2;
		float x = bounds.rect.x;
		float y = bounds.rect.y;
		
		node[0] = new QuadTree(level + 1, Rect({ x,y,halfWidth,halfHeight }));
		node[1] = new QuadTree(level + 1, Rect({ x + halfWidth,y,halfWidth,halfHeight }));
		node[2] = new QuadTree(level + 1, Rect({ x,y + halfHeight,halfWidth,halfHeight }));
		node[3] = new QuadTree(level + 1, Rect({ x + halfWidth,y + halfHeight,halfWidth,halfHeight }));
	}

	int getIndex(BaseObject* obj) {
		float verticalMidPoint = bounds.rect.x + bounds.rect.w / 2;
		float horizonMidPoint = bounds.rect.y + bounds.rect.h / 2;
		SDL_FRect r = obj->getHitBox()->rect;

		bool topQuadrant = (r.y < horizonMidPoint && r.y + r.h <= horizonMidPoint);
		bool bottomQuadrant = (r.y >= horizonMidPoint);
		bool leftQuadrant = (r.x < verticalMidPoint && r.x + r.w <= verticalMidPoint);
		bool rightQuadrant = (r.x >= verticalMidPoint);

		if (r.w > bounds.rect.w / 2 || r.h > bounds.rect.h / 2) {
			return -1;  // 物体太大，直接留在当前节点
		}

		if (topQuadrant && leftQuadrant) return 0;
		if (topQuadrant && rightQuadrant) return 1;
		if (bottomQuadrant && leftQuadrant) return 2;
		if (bottomQuadrant && rightQuadrant) return 3;
		return -1;
	}

	void insert(BaseObject* obj) {
		if (node[0]) {
			int idx = getIndex(obj);
			if (idx != -1) {
				node[idx]->insert(obj);
				return;
			}
		}

		objects.push_back(obj);

		if (objects.size() > MAX_OBJECTS && level < MAX_LEVEL) {
			if (!node[0]) subdivide();
			auto it = objects.begin();
			while (it != objects.end()) {
				int idx = getIndex(*it);
				if (idx != -1) {
					node[idx]->insert(*it);
					it = objects.erase(it);
				}
				else {
					++it;
				}

			}
		}
    }

	void retrieve(std::vector<BaseObject*>& returnObjects,BaseObject* obj) {
		int idx = getIndex(obj);
		if (node[0]) {
			if (idx == -1) {
				for (auto n : node) {
					n->retrieve(returnObjects,obj);
				}
			}
			else {
				node[idx]->retrieve(returnObjects, obj);
			}
		}
		returnObjects.insert(returnObjects.begin(),objects.begin(),objects.end());
	}

	void update_collision(std::vector<BaseObject*>& vObjects) {
		this->clear();
		for (auto o : vObjects) {
			this->insert(o);
		}
		for (auto obj : vObjects) {
			if (obj->getObjectType() == ObjectType::Ground) {
				continue;
			}
			std::vector<BaseObject*> possibleCollision;
			this->retrieve(possibleCollision,obj);
			for (auto other : possibleCollision) {
				if (obj == other) continue;
				if (obj->getHitBox()->intersects(*other->getHitBox())) {
					obj->on_collision(other);
				}
			}
		}
	}
};

