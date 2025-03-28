#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <graphics.h>
#include <cassert>
#include <filesystem>
#include <windows.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <functional>
#include <SDL3_ttf/SDL_ttf.h>
#include <array>
#include <queue>
#include "../json.hpp"
#include <fstream>
#include <stack>
#include <chrono>
#include <mmsystem.h>
#include <thread>
#include <cmath>


#include "config.h"
#include "game/GameWorld.h"
#include "utils/Random_utils.h"
#include "core/RendererManager.h"
#include "core/ResourceManager.h"
#include "core/timer.h"
#include "core/Statistics.h"
#include "core/InputManager.h"
#include "core/TextRenderer.h"
#include "core/Resolution.h"
#include "./objects/camera/Camera.h"
#include "core/ColorManager.h"

