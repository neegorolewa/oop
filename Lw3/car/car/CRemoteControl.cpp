#pragma once
#include "CCar.h"
#include "CRemoteControl.h"
#include "stdafx.h"

using namespace std;
using namespace std::placeholders;

map<Direction, std::string> directionMap = {
		{Direction::STANDING_STILL, "Standing still"},
		{Direction::FORWARD, "Forward"},
		{Direction::BACKWARD, "Backward"}
};

CRemoteControl::CRemoteControl(Car& car, istream& input, ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{"engineon", bind(&CRemoteControl::EngineOn, this, _1) },
		{"engineoff", bind(&CRemoteControl::EngineOff, this, _1)},
		{"info", bind(&CRemoteControl::Info, this, _1)},
		{"setgear", bind(&CRemoteControl::SetGear, this, _1)},
		{"setspeed", bind(&CRemoteControl::SetSpeed, this, _1)},
		{"exit", bind(&CRemoteControl::Exit, this, _1)},
		})
{
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);

	std::transform(commandLine.begin(), commandLine.end(), commandLine.begin(), [](unsigned char ch)
		{
			return std::tolower(ch);
		}
	);

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
	if (!m_car.IsTurned())
	{
		m_car.TurnOnEngine();
		m_output << ENGINE_IS_STARTED << endl;
	}
	else
	{
		m_output << ENGINE_ALREADY_STARTED << endl;
	}
	return true;
}

bool CRemoteControl::EngineOff(istream& args)
{
	if (!m_car.IsTurned())
	{
		m_output << ENGINE_ALREADY_TURN_OFF << endl;
	}
	else
	{
		if (m_car.TurnOffEngine())
		{
			m_output << ENGINE_IS_ENDED << endl;
		}
		else
		{
			m_output << ERROR_TURN_OFF_ENGINE << endl;
		}
	}
	
	return true;
}

bool CRemoteControl::Info(istream& args)
{
	string direction;
	Direction intDir = m_car.GetDirection();

	direction = directionMap[intDir];

	string stateCarWithoutEngine = '\n' + DIRECTION + direction + '\n' +
		SPEED + to_string(m_car.GetSpeed()) + '\n' + GEAR + to_string(m_car.GetGear());

	string info = (m_car.IsTurned())
		? (TURN_ON_ENGINE + stateCarWithoutEngine)
		: (TURN_OFF_ENGINE + stateCarWithoutEngine);

	m_output << info << endl;

	return true;
}

bool CRemoteControl::SetGear(istream& args)
{
	int gear;
	args >> gear;

	if (!args.fail())
	{
		if (m_car.SetGear(gear))
		{
			m_output << GEAR_MESSAGE_TRUE << gear << endl;
		}
		else
		{
			m_output << GEAR_MESSAGE_FALSE << gear << endl;
		}
		
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
		if (m_car.SetSpeed(speed))
		{
			m_output << SPEED_MESSAGE_TRUE << speed << endl;
		}
		else
		{
			m_output << SPEED_MESSAGE_FALSE << speed << endl;
		}

		return true;
	}
	else
	{
		m_output << INVALID_INPUT << endl;
		return false;
	}
}

bool CRemoteControl::Exit(istream& args)
{
	m_output << END_PROGRAM << endl;
	exit(1);
}
