#include "pch.h"
#include "transformUtils.h"

TransformUtils::TransformUtils()
{
	string2playerState = {
		{"Idle",PlayerState::Idle},
		{"Idle_to_Jump",PlayerState::Idle_to_Jump},
		{"Jump",PlayerState::Jump},
		{"Fall",PlayerState::Fall},
		{"Idle_to_Run",PlayerState::Idle_to_Run},
		{"Run",PlayerState::Run},
		{"Run_to_Idle",PlayerState::Run_to_Idle},
		{"Idle_to_Down",PlayerState::Idle_to_Down},
		{"Down",PlayerState::Down},
		{"Down_to_Idle",PlayerState::Down_to_Idle},
	};
}
