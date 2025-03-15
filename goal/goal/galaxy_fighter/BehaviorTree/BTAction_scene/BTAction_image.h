#pragma once
#include "../BTNode.h"
#include "../../objects/camera/Camera.h"
#include "../../core/Context.h"


namespace BTAction_image {
	class BTAction_image : public BTNode
	{

	};

	class display_full : public BTNode {
	private:
		SDL_FRect rect;
	public:
		display_full(shared_ptr<Context> context);//����������ʾ
		bool execute() override;
	};

	//��ʾͼƬ��ָ��λ��
	class display_at_position : public BTNode {
	public:
		display_at_position(SDL_Texture* texture, SDL_FRect* rect, double angle);
		bool execute();
	private:
		SDL_Texture* texture;
		SDL_FRect* rect;
		double angle;
	};

	class display_background: public BTNode {
	public:
		display_background(shared_ptr<Context> context);
		bool execute();
	private:
		Camera* camera;
	};

	//����
	class scaling_up_hovering :public BTNode {
	public:
		scaling_up_hovering(SDL_FRect& rect, float scaleFactor, float duration, bool& isSelecting);
		//ԭʼ���δ�С�����ŵİٷֱȣ�����ʱ��
		bool execute() override;

	private:

		SDL_FRect& rect;
		bool& isSelecting;
		SDL_FRect originalSize;
		float scaleFactor;
		float duration;
		float elapsed;
		float curScaleFactor;
	};



	class delay : public BTNode {
	public:
		delay(double delay_time);
		bool execute();
	private:
		double delay_time;
	};

	class check_hover : public BTNode {
	public:
		check_hover(SDL_FRect* rect);
		bool execute();
	private:
		SDL_FRect* rect;
	};
}


