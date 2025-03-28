#include "pch.h"
#include "SubState.h"
#include "../../utils/Math.h"
void SubNone::Enter(PlayerObject& player)
{
}

void SubNone::Update(PlayerObject& player)
{
}

void SubNone::Exit(PlayerObject& player)
{
}

std::string SubNone::GetState()
{
	return std::string();
}

void Rebound::Enter(PlayerObject& player)
{
	orientation = -player.getOrientation();

	acceleration = 1500 * orientation;
	actionTime = 1.0 / 60 * 10;
	elapsed = 0.0;
}

void Rebound::Update(PlayerObject& player)
{
	double delta = Timer::Instance().getDeltaAdjustTime();

	if (elapsed == actionTime) {
		player.setEventVelocityX(0);
		player.ChangeSubState(new SubNone);
		return;
	}
	elapsed += delta;
	if (elapsed > actionTime) {
		elapsed = actionTime;
		player.setEventVelocityX(Math::ExpInterpolation(acceleration, 0, 1));
		return;
	}

	double velocity = orientation * acceleration * delta;
	player.setEventVelocityX(Math::ExpInterpolation(acceleration,0,elapsed/actionTime));
}

void Rebound::Exit(PlayerObject& player)
{

}

std::string Rebound::GetState()
{
	return std::string();
}

Rebound::~Rebound() {
	cout << "rebound deleted" << endl;
}




