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


#include "config.h"
#include "game/gameWorld.h"
#include "utils/random_utils.h"
#include "core/rendererManager.h"
#include "core/resourceManager.h"
#include "core/timer.h"
#include "core/statistics.h"
#include "core/inputManager.h"
#include "core/textRenderer.h"
#include "core/Resolution.h"
#include "./objects/camera/Camera.h"

