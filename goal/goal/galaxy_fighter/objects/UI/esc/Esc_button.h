#pragma once
#include "../component.h"
#include "../../../BehaviorTree/paralle/ParalleNode.h"
class Esc_button : public component
{
	bool is_clicked;
	SDL_Texture* texture;
	std::shared_ptr<ParalleNode> root;
	bool is_selected = false;
public:
	Esc_button();
	void render() override;
	void update();

};

