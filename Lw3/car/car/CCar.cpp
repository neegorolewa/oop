#include <iostream>
#include "CCar.h"

bool Car::IsTurned() const
{
	return m_engineOn;
}

Direction Car::GetDirection() const
{
	return m_dir;
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

	return m_engineOn;
}

bool Car::TurnOffEngine()
{
	if ((m_engineOn && m_gear == MIN_SPEED && m_speed == MIN_SPEED) || (!m_engineOn))
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
	if (!m_engineOn)
	{
		return false;
	}

	if (((GetDirection() == Direction::BACKWARD) && (gear > 0)) 
		|| ((GetDirection() == Direction::FORWARD) && (gear == REVERSE)) 
		|| ((gear == REVERSE) && (m_speed != MIN_SPEED)))
	{
		return false;
	}

	auto gearSpeed = gearSpeedRange.find(gear);

	if (gearSpeed == gearSpeedRange.end())
	{
		return false;
	}

	int gearSpeedMin = gearSpeed->second.first;
	int gearSpeedMax = gearSpeed->second.second;

	if (m_speed < gearSpeedMin || m_speed > gearSpeedMax)
	{
		return false;
	}

	if (gear == 1 && m_dir == Direction::BACKWARD)
	{
		return false;
	}

	if (m_gear == NEUTRAL_GEAR)
	{
		m_gear = gear;
		return true;
	}

	m_gear = gear;

	return true;
}

bool Car::SetSpeed(int speed)
{
	if (!m_engineOn)
	{
		return false;
	}

	if (m_gear == NEUTRAL_GEAR)
	{
		if (speed < m_speed)
		{
			m_speed = speed;
			if (speed == MIN_SPEED)
			{
				m_dir = Direction::STANDING_STILL;
			}

			return true;
		}
		else
		{
			return false;
		}
	}
	
	auto gearSpeed = gearSpeedRange.find(m_gear);

	if (gearSpeed == gearSpeedRange.end())
	{
		return false;
	}

	int gearSpeedMin = gearSpeed->second.first;
	int gearSpeedMax = gearSpeed->second.second;

	switch (m_gear)
	{
	case REVERSE:
		if (speed >= gearSpeedMin && speed <= gearSpeedMax)
		{
			m_speed = speed;
			if (speed == MIN_SPEED)
			{
				m_dir = Direction::STANDING_STILL;
			}
			else
			{
				m_dir = Direction::BACKWARD;
			}

			return true;
		}
		break;
	case 1:
		if (speed >= gearSpeedMin && speed <= gearSpeedMax)
		{
			m_speed = speed;
			if (speed == MIN_SPEED)
			{
				m_dir = Direction::STANDING_STILL;
			}
			else
			{
				m_dir = Direction::FORWARD;
			}

			return true;
		}
		break;
	default:
		if (speed >= gearSpeedMin && speed <= gearSpeedMax)
		{
			m_speed = speed;
			return true;
		}
		break;

	}

	return false;

}
