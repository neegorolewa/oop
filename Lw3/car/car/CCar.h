#pragma once
#include "stdafx.h"

const std::string INVALID_INPUT = "Invalid input data";
const std::string TURN_ON_ENGINE = "Engine: On";
const std::string TURN_OFF_ENGINE = "Engine: Off";
const std::string DIRECTION = "Direction: ";
const std::string SPEED = "Speed: ";
const std::string GEAR = "Gear: ";
const std::string ERROR_SET_GEAR = "Error setting gear";
const std::string ENGINE_IS_STARTED = "Engine is turned on";
const std::string ENGINE_ALREADY_STARTED = "The engine has already started";
const std::string ENGINE_IS_ENDED = "Engine is turned off";
const std::string ENGINE_ALREADY_TURN_OFF = "The engine already turned off";
const std::string ERROR_TURN_OFF_ENGINE = "The engine can't be turned off";
const std::string GEAR_MESSAGE_TRUE = "Gear set ";
const std::string GEAR_MESSAGE_FALSE= "Gear can't be set ";
const std::string SPEED_MESSAGE_TRUE = "Speed set ";
const std::string SPEED_MESSAGE_FALSE = "Speed can't be set ";
const std::string END_PROGRAM = "Program is ended";

const std::string MENU = R"(
Info: Output state of engine status, driving direction, speed and gear
EngineOn: Turn on engine
EngineOff: Turn off engine
SetGear gear
SetSpeed speed
Exit: End program
)";

const int NEUTRAL_GEAR = 0;
const int MIN_SPEED = 0;
const int REVERSE = -1;
const int MAX_SPEED = 150;

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
	int m_gear = NEUTRAL_GEAR;
	int m_speed = MIN_SPEED;
	Direction m_dir = Direction::STANDING_STILL;
	std::map<int, std::pair<int, int>> gearSpeedRange = {
	{-1, {0, 20}},
	{0, {0, 150}},
	{1, {0, 30}},
	{2, {20, 50}},
	{3, {30, 60}},
	{4, {40, 90}},
	{5, {50, 150}},
	};
};