#pragma once
#include "../../pch.h"
#include "Scene.h"

using namespace std;

class MenuScene :
    public Scene
{
public:
    MenuScene() = default;
    ~MenuScene() = default;
    void on_enter() {
        cout << "进入主菜单" << endl;
    }

    void on_update() {
        cout << "主菜单正在运行..." << endl;
    }

    void on_draw() {

    }
private:

};

