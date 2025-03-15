#pragma once
#include "pch.h"
#include "InputBuffer.h"
#include "Composite/Selector.h"
#include "Composite/Sequence.h"
#include "BTAction_player/BTAction_player.h"
#include "BTAction_scene/BTAction_image.h"
#include "../core/Context.h"

using json = nlohmann::json;
using namespace std;


shared_ptr<BTNode> createNodeFromJson(const json& nodeConfig, shared_ptr<Context> context);


