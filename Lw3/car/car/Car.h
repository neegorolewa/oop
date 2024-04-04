#pragma once
#include "stdafx.h"

const std::string INVALID_INPUT = "Invalid input data";
const std::string  SEPARATOR = " / ";
const std::string DIRECTION = "Direction: ";
const std::string SPEED = "Speed: ";
const std::string GEAR = "Gear: ";
const std::string ERROR_SET_GEAR = "error setting gear";
const std::string ENGINE_ALREADY_TURN_OFF = "the engine already turned off";
const std::string TURN_OFF_ENGINE = "Engine: Off";
const std::string ENGINE_ALREADY_STARTED = "the engine has already started";
const std::string TURN_ON_ENGINE = "Engine: On";
const int ZERO = 0;
const int REVERSE = -1;
const int FIRST = 1;
const int SECOND = 2;
const int THIRD = 3;
const int FOURTH = 4;
const int FIFTH = 5;
const int TWENTY = 20;
const int THIRTY = 30;
const int FIFTY = 50;
const int FORTY = 40;
const int SIXTY = 60;
const int NINETY = 90;
const int ONE_HUNDRED_FIFTY = 150;

enum class Direction 
{
	STANDING_STILL,
	BACKWARD,
	FORWARD,
};

class Car 
{
public:

	bool IsTurned() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:

	bool m_engineOn = false;
	int m_gear = ZERO;
	int m_speed = ZERO;
	Direction m_state = Direction::STANDING_STILL;
};