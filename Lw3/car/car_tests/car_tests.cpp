#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../car/Car.h"

Car car;

SCENARIO("Make car and check speed, gear, engine")
{
	REQUIRE(car.IsTurned() == false);
	REQUIRE(car.GetSpeed() == ZERO);
	REQUIRE(car.GetGear() == ZERO);
}

SCENARIO("Turn on engine")
{
	car.TurnOnEngine();
	REQUIRE(car.IsTurned());
}

SCENARIO("Turn on engine several time")
{
	car.TurnOnEngine();
	REQUIRE(car.IsTurned());
	car.TurnOnEngine();
	REQUIRE(car.IsTurned());
}

SCENARIO("Turn off engine")
{
	car.TurnOnEngine();
	car.TurnOffEngine();
	REQUIRE(!car.IsTurned());
}

SCENARIO("Turn off engine several time")
{
	car.TurnOnEngine();
	car.TurnOffEngine();
	car.TurnOffEngine();
	REQUIRE(!car.IsTurned());
}

SCENARIO("After turn on engine car is standing still")
{
	car.TurnOnEngine();
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
}

SCENARIO("Neutral gear do not give pick up speed")
{
	car.TurnOnEngine();
	car.SetSpeed(10);
	REQUIRE(car.GetSpeed() == 0);
}

SCENARIO("if speed = 0 and turn on neutral")
{
	car.TurnOnEngine();

	WHEN("Switch to reverse gear")
	{
		car.SetGear(-1);
		THEN("Car should be turn on reverse gear")
		{
			REQUIRE(car.GetGear() == -1);
		}
	}

	WHEN("Switch to first gear")
	{
		car.SetGear(1);
		THEN("Car should be turn on first gear")
		{
			REQUIRE(car.GetGear() == 1);
		}
	}
}

SCENARIO("Reverse gear don't turn on if speed != 0")
{
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);
	car.SetGear(-1);
	REQUIRE(car.GetGear() != -1);
}

SCENARIO("Reverse gear engages after neutral when speed = 0")
{
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);
	car.SetSpeed(0);
	car.SetGear(-1);
	REQUIRE(car.GetGear() == -1);
}

SCENARIO("switch from reverse to forward gear only at zero speed")
{
	car.TurnOnEngine();
	car.SetGear(-1);

	WHEN("Speed != 0")
	{
		car.SetSpeed(20);
		car.SetGear(1);
		THEN("Gear don't switch")
		{
			REQUIRE(car.GetGear() != 1);
		}
	}

	WHEN("Speed = 0 after reverse gear")
	{
		car.SetSpeed(20);
		car.SetSpeed(0);
		car.SetGear(1);
		THEN("First gear turn on")
		{
			REQUIRE(car.GetGear() == 1);
		}
	}
}

SCENARIO("Switched to neutral gear in reverse at when speed != 0, switch to forward gear only after stopping")
{
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(15);
	car.SetGear(0);
	
	WHEN("Speed != 0")
	{
		car.SetGear(1);
		THEN("Forward gear don't turn on")
		{
			REQUIRE(car.GetGear() != 1);
		}
	}

	WHEN("Speed = 0")
	{
		car.SetSpeed(0);
		car.SetGear(1);
		THEN("Forward gear turn on")
		{
			REQUIRE(car.GetGear() == 1);
		}
	}
}

SCENARIO("Can shift from any gear to any, provided that the current speed of the car is within the speed range")
{
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);

	WHEN("Current speed not in range next gear")
	{
		car.SetGear(4);
		THEN("Gear not be turn on")
		{
			REQUIRE(car.GetGear() != 4);
		}
	}

	WHEN("Current speed in range next gear")
	{
		car.SetGear(2);
		THEN("Gear be turn on")
		{
			REQUIRE(car.GetGear() == 2);
		}
	}
}

SCENARIO("The engine can only be turned off at zero speed in neutral")
{
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(50);
	
	WHEN("Speed != 0 and gear not neutral")
	{
		car.TurnOffEngine();
		THEN("Engine is not turned off")
		{
			REQUIRE(car.IsTurned());
		}
	}

	car.SetSpeed(20);
	car.SetGear(1);
	car.SetSpeed(0);

	WHEN("Speed = 0 and gear not neutral")
	{
		car.TurnOffEngine();
		THEN("Engine is not turned off")
		{
			REQUIRE(car.IsTurned());
		}
	}

	WHEN("Speed = 0 and gear neutral")
	{
		car.SetGear(0);
		car.TurnOffEngine();
		THEN("Engine is turned off")
		{
			REQUIRE(!car.IsTurned());
		}
	}
}