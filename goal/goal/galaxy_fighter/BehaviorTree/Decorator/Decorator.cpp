#include "pch.h"
#include "Decorator.h"

Decorator::Decorator(std::unique_ptr<BTNode> child) : child(move(child)) {  }
