#pragma once
#include "../BTNode.h"
#include "../../objects/playerObject/playerObject.h"


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
        
        SDL_FRect* srcRect;//精灵表矩形坐标
        SDL_FRect* parentRect;
        
        SDL_FRect rect_show;

        SDL_FRect* windowRect;
        double angle;
        double anime_play_time;
    public:
        display_anime_at_center(SDL_Texture* texture, SDL_FRect* srcRect ,SDL_FRect* parentRect, double angle);
        bool execute();

    };

    class player_move_image :
        public BTNode 
    {
        PlayerObject& player;
        float limitWidth, limitHeight;
    public:
        player_move_image(PlayerObject& player);
        bool execute();
    };

    class player_move_sprite :
        public BTNode
    {
        PlayerObject& player;
        float limitWidth, limitHeight;
    public:
        player_move_sprite(PlayerObject& player);
        bool execute();
    };

    class cal_sprite_rect :
        public BTNode
    {
    public:
        cal_sprite_rect();
        bool execute();
    };
}




