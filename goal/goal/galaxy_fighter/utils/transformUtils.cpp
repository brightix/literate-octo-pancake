#include "pch.h"
#include "transformUtils.h"

TransformUtils::TransformUtils()
{
	string2playerState = {
		{"Idle",PlayerState::Idle},
		{"Jump",PlayerState::Jump},
		{"Left",PlayerState::Left},
		{"Down",PlayerState::Down},
		{"Right",PlayerState::Right},
	};
}
