#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../car/CCar.h"

SCENARIO("Make car and check speed, gear, engine")
{
	Car car;

	REQUIRE(car.IsTurned() == false);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);
}

SCENARIO("Turn on engine")
{
	Car car;

	car.TurnOnEngine();
	REQUIRE(car.IsTurned());
}

SCENARIO("Turn on engine several time")
{
	Car car;

	car.TurnOnEngine();
	REQUIRE(car.IsTurned());
	car.TurnOnEngine();
	REQUIRE(car.IsTurned());
}

SCENARIO("Turn off engine")
{
	Car car;

	car.TurnOnEngine();
	car.TurnOffEngine();
	REQUIRE(!car.IsTurned());
}

SCENARIO("Turn off engine several time")
{
	Car car;

	car.TurnOnEngine();
	car.TurnOffEngine();
	car.TurnOffEngine();
	REQUIRE(!car.IsTurned());
}

SCENARIO("Work with car when engine is off")
{
	Car car;

	REQUIRE(!car.IsTurned());
	WHEN("Set speed")
	{
		car.SetSpeed(20);
		THEN("Speed don't be set")
		{
			REQUIRE(car.GetSpeed() == 0);
		}
	}
	WHEN("Set gear")
	{
		car.SetGear(1);
		THEN("Gear don't be set")
		{
			REQUIRE(car.GetGear() == 0);
		}
	}
}

SCENARIO("After turn on engine car is standing still")
{
	Car car;

	car.TurnOnEngine();
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
}

SCENARIO("Neutral gear do not give pick up speed")
{
	Car car;

	car.TurnOnEngine();
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetSpeed() == 0);
	car.SetSpeed(10);
	REQUIRE(car.GetSpeed() == 0);
	car.SetSpeed(60);
	REQUIRE(car.GetSpeed() == 0);
}

SCENARIO("if speed = 0 and turn on neutral")
{
	Car car;

	car.TurnOnEngine();
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);

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
	Car car;

	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);
	car.SetGear(-1);
	REQUIRE(car.GetGear() != -1);
}

SCENARIO("Reverse gear engages after neutral when speed = 0")
{
	Car car;

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
	Car car;

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
	Car car;

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
	Car car;

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
	Car car;

	REQUIRE(!car.IsTurned());
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

SCENARIO("Test set gear -1 -> set speed in range 1 gear -> 1 -> 2")
{
	Car car;

	car.TurnOnEngine();
	car.SetGear(-1);
	REQUIRE(car.GetGear() == -1);
	car.SetSpeed(15);
	REQUIRE(car.GetSpeed() == 15);
	car.SetGear(1);
	REQUIRE(car.GetGear() != 1);
	car.SetGear(2);
	REQUIRE(car.GetGear() != 2);
}

SCENARIO("Check range speed of gear -1")
{
	Car car;

	car.TurnOnEngine();
	car.SetGear(-1);

	car.SetSpeed(0);
	REQUIRE(car.GetSpeed() == 0);

	car.SetSpeed(20);
	REQUIRE(car.GetSpeed() == 20);

	car.SetSpeed(10);
	REQUIRE(car.GetSpeed() == 10);

	car.SetSpeed(30);
	REQUIRE(car.GetSpeed() != 30);
}

SCENARIO("Check range speed of gear 1")
{
	Car car;

	car.TurnOnEngine();
	car.SetGear(1);

	car.SetSpeed(0);
	REQUIRE(car.GetSpeed() == 0);

	car.SetSpeed(30);
	REQUIRE(car.GetGear() == 1);
	REQUIRE(car.GetSpeed() == 30);

	car.SetSpeed(15);
	REQUIRE(car.GetSpeed() == 15);

	car.SetSpeed(40);
	REQUIRE(car.GetSpeed() != 40);
}

SCENARIO("Check range speed of gear 2")
{
	Car car;

	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);

	car.SetSpeed(20);
	REQUIRE(car.GetSpeed() == 20);
	car.SetSpeed(50);
	REQUIRE(car.GetSpeed() == 50);
	car.SetSpeed(30);
	REQUIRE(car.GetSpeed() == 30);
	car.SetSpeed(70);
	REQUIRE(car.GetSpeed() != 70);
	car.SetSpeed(10);
	REQUIRE(car.GetSpeed() != 10);
}

SCENARIO("Check range speed of gear 3")
{
	Car car;

	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	car.SetSpeed(30);
	car.SetGear(3);

	car.SetSpeed(30);
	REQUIRE(car.GetSpeed() == 30);
	car.SetSpeed(60);
	REQUIRE(car.GetSpeed() == 60);
	car.SetSpeed(45);
	REQUIRE(car.GetSpeed() == 45);
	car.SetSpeed(70);
	REQUIRE(car.GetSpeed() != 80);
	car.SetSpeed(10);
	REQUIRE(car.GetSpeed() != 15);
}

SCENARIO("Check range speed of gear 4")
{
	Car car;

	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(40);
	car.SetGear(4);

	car.SetSpeed(40);
	REQUIRE(car.GetSpeed() == 40);
	car.SetSpeed(90);
	REQUIRE(car.GetSpeed() == 90);
	car.SetSpeed(65);
	REQUIRE(car.GetSpeed() == 65);
	car.SetSpeed(100);
	REQUIRE(car.GetSpeed() != 100);
	car.SetSpeed(30);
	REQUIRE(car.GetSpeed() != 30);
}

SCENARIO("Check range speed of gear 5")
{
	Car car;

	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(40);
	car.SetGear(4);
	car.SetSpeed(50);
	car.SetGear(5);

	car.SetSpeed(50);
	REQUIRE(car.GetSpeed() == 50);
	car.SetSpeed(150);
	REQUIRE(car.GetSpeed() == 150);
	car.SetSpeed(100);
	REQUIRE(car.GetSpeed() == 100);
	car.SetSpeed(200);
	REQUIRE(car.GetSpeed() != 200);
	car.SetSpeed(49);
	REQUIRE(car.GetSpeed() != 49);
}