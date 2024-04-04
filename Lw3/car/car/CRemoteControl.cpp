#pragma once
#include "Car.h"
#include "CRemoteControl.h"
#include "stdafx.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(Car& car, istream& input, ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{"EngineOn", [this](istream& strm) {
			return EngineOn(strm);
		} },
		{"EngineOff", bind(&CRemoteControl::EngineOff, this, _1)},
		{"Info", bind(&CRemoteControl::Info, this, _1)},
		{"SetGear", bind(&CRemoteControl::SetGear, this, _1)},
		{"SetSpeed", bind(&CRemoteControl::SetSpeed, this, _1)},
		})
{
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CRemoteControl::EngineOn(istream& args)
{
	m_car.TurnOnEngine();
	return true;
}

bool CRemoteControl::EngineOff(istream& args)
{
	m_car.TurnOffEngine();
	return true;
}

bool CRemoteControl::Info(istream& args)
{
	string direction;
	Direction intDir = m_car.GetDirection();

	switch (intDir)
	{
	case Direction::STANDING_STILL:
		direction = "Standing still";
		break;
	case Direction::FORWARD:
		direction = "Forward";
		break;
	case Direction::BACKWARD:
		direction = "Backward";
		break;
	}

	string info = (m_car.IsTurned())
		? (TURN_ON_ENGINE + SEPARATOR + DIRECTION + direction + SEPARATOR +
			SPEED + to_string(m_car.GetSpeed()) + SEPARATOR + GEAR + to_string(m_car.GetGear()))
		: (TURN_OFF_ENGINE + SEPARATOR + DIRECTION + direction + SEPARATOR +
			SPEED + to_string(m_car.GetSpeed()) + SEPARATOR + GEAR + to_string(m_car.GetGear()));

	m_output << info << endl;

	return true;
}

bool CRemoteControl::SetGear(istream& args)
{
	int gear;
	args >> gear;

	if (!args.fail())
	{
		m_car.SetGear(gear);
		m_output << GEAR << gear << endl;
		return true;
	}
	else
	{
		m_output << INVALID_INPUT << endl;
		return false;
	}
}

bool CRemoteControl::SetSpeed(istream& args)
{
	int speed;
	args >> speed;

	if (!args.fail())
	{
		m_car.SetSpeed(speed);
		m_output << SPEED << speed << endl;
		return true;
	}
	else
	{
		m_output << INVALID_INPUT << endl;
		return false;
	}
}