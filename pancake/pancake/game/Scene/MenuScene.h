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
        cout << "�������˵�" << endl;
    }

    void on_update() {
        cout << "���˵���������..." << endl;
    }

    void on_draw() {

    }
private:

};

