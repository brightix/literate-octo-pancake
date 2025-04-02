#pragma once
#include "pch.h"
#include "Event.h"
#include "../CreatorComponent.h"
#include <typeindex>
class EventSystem
{
	std::queue<Event*> Events;
	std::unordered_map<std::type_index, std::vector<CreatorComponent*>> listeners;
public:
	EventSystem() {}
	void subscribe(std::type_index eventType,CreatorComponent* listener) {
		listeners[eventType].push_back(listener);
	}

	void queueEvent(Event* event) {
		Events.push(event);
	}
	void processEvents() {
		while (!Events.empty()) {
			Event* e = Events.front();
			auto it = listeners.find(typeid(*e));
			if (it != listeners.end()) {
				for (auto* listener : it->second) {
					listener->onEvent(e);
				}
			}
			delete e;
			Events.pop();
		}
	}
};

