#pragma once
#include "../BTNode.h"
#include "../../objects/playerObject/playerObject.h"
#include "../InputBuffer.h"

namespace BTAction_player {
    class BTAction_player :
        public BTNode
    {

    };


    class display_at_position :
        public BTNode
    {
        SDL_Texture* texture;
        SDL_FRect* rect;
        double angle;
    public:
        display_at_position(SDL_Texture* texture, SDL_FRect* rect, double angle);
        bool execute();
    };

    class display_at_center :
        public BTNode
    {
        SDL_Texture* texture;

        SDL_FRect* parentRect;//父矩形
        SDL_FRect rect_show;//作位目标位置的矩形

        SDL_FRect* windowRect;
        double angle;
    public:
        display_at_center(SDL_Texture* texture, SDL_FRect* parentRect, double angle);
        bool execute();
    };


    class display_anime_at_center :
        public BTNode 
    {
        SDL_Texture* texture;
        
        SDL_FRect& spriteFrameRect;//精灵表矩形坐标
        SDL_FRect* parentRect;
        
        SDL_FRect rect_show;

        SDL_FRect* windowRect;

        bool* isTowardRight;
        double angle;
    public:
        display_anime_at_center(SDL_Texture* texture, SDL_FRect& spriteFrameRect ,SDL_FRect* parentRect, double angle,bool* isTowardRight);
        bool execute();

    };

    class player_move_image :
        public BTNode 
    {
        float limitWidth, limitHeight;
    public:
        player_move_image(shared_ptr<Context> context);
        bool execute();
    };

    class CheckComboNode : public BTNode {
        vector<string> combo;
        InputBuffer& inputBuffer;
    public:
        CheckComboNode(const vector<string>& combo,InputBuffer& buf) : combo(combo),inputBuffer(buf){}
        bool execute() override;
    };

    class player_detect_input :
        public BTNode 
    {
    public:
        player_detect_input(shared_ptr<Context> context);
        bool execute();
    };

    class player_move_jump :
        public BTNode 
    {
    public:
        player_move_jump(shared_ptr<Context> context);
        bool execute();
    };

    class player_move_down:
        public BTNode
    {
    public:
        player_move_down(shared_ptr<Context> context);
        bool execute();
    };

    class player_move_left :
        public BTNode
    {
    public:
        player_move_left(shared_ptr<Context> context);
        bool execute();
    };

    class player_move_right :
        public BTNode
    {
    public:
        player_move_right(shared_ptr<Context> context);
        bool execute();
    };

    class refreshRect :
        public BTNode
    {
    public:
        refreshRect(shared_ptr<Context> context);
        bool execute();
    };

    //class isPlayer :
    //    public BTNode
    //{
    //public:
    //    refreshRect(shared_ptr<Context> context);
    //    bool execute();
    //};
}




