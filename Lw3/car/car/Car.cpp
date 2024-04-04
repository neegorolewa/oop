#include <iostream>
#include "Car.h"

std::map<int, std::pair<int, int>> gearSpeedRange = {
	{REVERSE, {ZERO, TWENTY}},
	{ZERO, {ZERO, ONE_HUNDRED_FIFTY}},
	{FIRST, {ZERO, THIRTY}},
	{SECOND, {TWENTY, FIFTY}},
	{THIRD, {THIRTY, SIXTY}},
	{FOURTH, {FORTY, NINETY}},
	{FIFTH, {FIFTY, ONE_HUNDRED_FIFTY}},
};

bool Car::IsTurned() const
{
	return m_engineOn;
}

Direction Car::GetDirection() const
{
	if ((m_gear == ZERO) && (m_speed > 0))
	{
		return m_state;
	}
	else
	{
		if (m_speed == ZERO)
		{
			return Direction::STANDING_STILL;
		}
		else if ((m_gear == REVERSE) && (m_speed > 0))
		{
			return Direction::BACKWARD;
		}
		else
		{
			return Direction::FORWARD;
		}
	}
}

int Car::GetSpeed() const
{
	return abs(m_speed);
}

int Car::GetGear() const
{
	return m_gear;
}

bool Car::TurnOnEngine()
{
	if (!m_engineOn)
	{
		m_engineOn = true;
	}

	return true;
}

bool Car::TurnOffEngine()
{
	if ((m_engineOn && m_gear == ZERO && m_speed == ZERO) || (!m_engineOn))
	{
		m_engineOn = false;

		return true;
	}
	else
	{
		return false;
	}
}

bool Car::SetGear(int gear)
{
	m_state = GetDirection();

	if (gear < REVERSE && gear > FIFTH)
	{
		return false;
	}

	if (!m_engineOn)
	{
		return false;
	}

	if (((GetDirection() == Direction::BACKWARD) && (gear == FIRST)) 
		|| ((GetDirection() == Direction::FORWARD) && (gear == REVERSE)) 
		|| ((gear == REVERSE) && (m_speed != ZERO)))
	{
		return false;
	}

	auto gearSpeed = gearSpeedRange.find(gear);

	if (gearSpeed == gearSpeedRange.end())
	{
		return false;
	}

	int gearSpeedMin = ZERO;
	int gearSpeedMax = ZERO;

	gearSpeedMin = gearSpeed->second.first;
	gearSpeedMax = gearSpeed->second.second;

	if (m_speed < gearSpeedMin || m_speed > gearSpeedMax)
	{
		return false;
	}

	if (m_gear == ZERO)
	{
		m_gear = gear;
		return true;
	}

	m_gear = gear;

	return true;
}

bool Car::SetSpeed(int speed)
{
	if (speed < ZERO || speed > ONE_HUNDRED_FIFTY)
	{
		return false;
	}

	if (!m_engineOn)
	{
		return false;
	}

	if (m_gear == ZERO && m_speed == ZERO)
	{
		return false;
	}

	if (m_gear == ZERO && speed < m_speed)
	{
		m_speed = speed;
		return true;
	}
	
	auto gearSpeed = gearSpeedRange.find(m_gear);

	if (gearSpeed == gearSpeedRange.end())
	{
		return false;
	}

	int gearSpeedMin = gearSpeed->second.first;
	int gearSpeedMax = gearSpeed->second.second;

	if (speed < gearSpeedMin || speed > gearSpeedMax)
	{
		return false;
	}

	m_speed = speed;

	return true;

}
