﻿#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../RationalNumbers/CRational.h"

TEST_CASE("Create numbers")
{
	WHEN("number = 0")
	{
		CRational number;
		THEN("num = 0, den = 1")
		{
			REQUIRE(number.GetNumerator() == 0);
			REQUIRE(number.GetDenominator() == 1);
		}
	}

	WHEN("number = 5")
	{
		CRational number(5);
		THEN("num = 5, den = 1")
		{
			REQUIRE(number.GetNumerator() == 5);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == 5.0);
		}
	}

	WHEN("number = 3/4")
	{
		CRational number(3, 4);
		THEN("num = 3, den = 4")
		{
			REQUIRE(number.GetNumerator() == 3);
			REQUIRE(number.GetDenominator() == 4);
			REQUIRE(number.ToDouble() == 0.75);
		}
	}

	WHEN("numerator set 0")
	{
		CRational number(0, 3);
		THEN("set rational numbers num = 0, den = 1")
		{
			REQUIRE(number.GetNumerator() == 0);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == 0);
		}
	}

	WHEN("number < 0 (numerator < 0)")
	{
		CRational number(-2, 5);
		THEN("num = -2, denominator = 5")
		{
			REQUIRE(number.GetNumerator() == -2);
			REQUIRE(number.GetDenominator() == 5);
			REQUIRE(number.ToDouble() == -0.4);
		}
	}

	WHEN("number < 0 (denominator < 0)")
	{
		CRational number(2, -5);
		THEN("num = -2, denominator = 5")
		{
			REQUIRE(number.GetNumerator() == -2);
			REQUIRE(number.GetDenominator() == 5);
			REQUIRE(number.ToDouble() == -0.4);
		}
	}

	WHEN("denominator = 0")
	{
		THEN("will be thrown exception")
		{
			try
			{
				CRational(1, 0);
			}
			catch (std::invalid_argument e)
			{
				e.what() == "Denominator cannot be zero.";
			}
		}
	}
}

TEST_CASE("Check unary operation")
{
	WHEN("unaru +")
	{
		CRational number(-3, 4);
		number = +number;
		THEN("number is -3/4")
		{
			REQUIRE(number.GetNumerator() == -3);
			REQUIRE(number.GetDenominator() == 4);
			REQUIRE(number.ToDouble() == -0.75);
		}
	}

	WHEN("unaru -")
	{
		CRational number(-3, 4);
		number = -number;
		THEN("number is 3/4")
		{
			REQUIRE(number.GetNumerator() == 3);
			REQUIRE(number.GetDenominator() == 4);
			REQUIRE(number.ToDouble() == 0.75);
		}
	}
}

TEST_CASE("Check binary operation + -")
{
	WHEN("bin +")
	{
		CRational num1(2, 3);
		CRational num2(1, 3);
		CRational res = num1 + num2;
		THEN("res = 1")
		{
			REQUIRE(res.GetNumerator() == 1);
			REQUIRE(res.GetDenominator() == 1);
			REQUIRE(res.ToDouble() == 1);
		}
	}

	WHEN("bin + (diff denominator)")
	{
		CRational num1(1, 3);
		CRational num2(1, 2);
		CRational res = num1 + num2;
		THEN("res = 5/6")
		{
			REQUIRE(res.GetNumerator() == 5);
			REQUIRE(res.GetDenominator() == 6);
			REQUIRE(res.ToDouble() == static_cast<double>(5) / 6);
		}
	}

	WHEN("num + int")
	{
		CRational num1(1, 3);
		CRational res = num1 + 1;
		THEN("res = 4/3")
		{
			REQUIRE(res.GetNumerator() == 4);
			REQUIRE(res.GetDenominator() == 3);
			REQUIRE(res.ToDouble() == static_cast<double>(4) / 3);
		}
	}

	WHEN("int + num")
	{
		CRational num1(1, 3);
		CRational res = 1 + num1;
		THEN("res = 4/3")
		{
			REQUIRE(res.GetNumerator() == 4);
			REQUIRE(res.GetDenominator() == 3);
			REQUIRE(res.ToDouble() == static_cast<double>(4) / 3);
		}
	}

	WHEN("bin -")
	{
		CRational num1(2, 3);
		CRational num2(1, 3);
		CRational res = num1 - num2;
		THEN("res = 1/3")
		{
			REQUIRE(res.GetNumerator() == 1);
			REQUIRE(res.GetDenominator() == 3);
			REQUIRE(res.ToDouble() == static_cast<double>(1) / 3);
		}
	}

	WHEN("int - num")
	{
		CRational num1(1, 2);
		CRational res = 1 - num1;
		THEN("res = 1/2")
		{
			REQUIRE(res.GetNumerator() == 1);
			REQUIRE(res.GetDenominator() == 2);
			REQUIRE(res.ToDouble() == 0.5);
		}
	}

	WHEN("num - int")
	{
		CRational num1(1, 2);
		CRational res = num1 - 1;
		THEN("res = -1/2")
		{
			REQUIRE(res.GetNumerator() == -1);
			REQUIRE(res.GetDenominator() == 2);
			REQUIRE(res.ToDouble() == -0.5);
		}
	}
}

TEST_CASE("+=, -=")
{
	WHEN("+=")
	{
		CRational num1(1, 2);
		CRational num2(1, 6);
		num1 += num2;
		THEN("num1 = 2/3")
		{
			REQUIRE(num1.GetNumerator() == 2);
			REQUIRE(num1.GetDenominator() == 3);
			REQUIRE(num1.ToDouble() == static_cast<double>(2) / 3);
		}
	}

	WHEN("num += int")
	{
		CRational num(1, 2);
		num += 1;
		THEN("num = 3/2")
		{
			REQUIRE(num.GetNumerator() == 3);
			REQUIRE(num.GetDenominator() == 2);
			REQUIRE(num.ToDouble() == 1.5);
		}
	}

	WHEN("-=")
	{
		CRational num1(1, 2);
		CRational num2(1, 6);
		num1 -= num2;
		THEN("num1 = 1/3")
		{
			REQUIRE(num1.GetNumerator() == 1);
			REQUIRE(num1.GetDenominator() == 3);
			REQUIRE(num1.ToDouble() == static_cast<double>(1) / 3);
		}
	}

	WHEN("num -= int")
	{
		CRational num(1, 2);
		num -= 1;
		THEN("res = -1/2")
		{
			REQUIRE(num.GetNumerator() == -1);
			REQUIRE(num.GetDenominator() == 2);
			REQUIRE(num.ToDouble() == -0.5);
		}
	}
}

TEST_CASE("* /")
{
	WHEN("*")
	{
		CRational num1(2, 3);
		CRational num2(1, 2);
		CRational res = num1 * num2;
		THEN("res = 2/6 -> 1/3")
		{
			REQUIRE(res.GetNumerator() == 1);
			REQUIRE(res.GetDenominator() == 3);
			REQUIRE(res.ToDouble() == static_cast<double>(1) / 3);
		}
	}

	WHEN("num * int")
	{
		CRational num(1, 2);
		CRational res = num * (-3);
		THEN("res = -3/2")
		{
			REQUIRE(res.GetNumerator() == -3);
			REQUIRE(res.GetDenominator() == 2);
			REQUIRE(res.ToDouble() == -1.5);
		}
	}

	WHEN("int * num")
	{
		CRational num(2, 3);
		CRational res = 7 * num;
		THEN("res = 14/3")
		{
			REQUIRE(res.GetNumerator() == 14);
			REQUIRE(res.GetDenominator() == 3);
			REQUIRE(res.ToDouble() == static_cast<double>(14) / 3);
		}
	}

	WHEN("/")
	{
		CRational num1(2, 3);
		CRational num2(1, 2);
		CRational res = num2 / num1;
		THEN("res = 3/4")
		{
			REQUIRE(res.GetNumerator() == 3);
			REQUIRE(res.GetDenominator() == 4);
			REQUIRE(res.ToDouble() == 0.75);
		}
	}

	WHEN("num / int")
	{
		CRational num(1, 2);
		CRational res = num / 5;
		THEN("res = 1/10")
		{
			REQUIRE(res.GetNumerator() == 1);
			REQUIRE(res.GetDenominator() == 10);
			REQUIRE(res.ToDouble() == 0.1);
		}
	}

	WHEN("int / num")
	{
		CRational num(2, 3);
		CRational res = 7 / num;
		THEN("res = 21/2")
		{
			REQUIRE(res.GetNumerator() == 21);
			REQUIRE(res.GetDenominator() == 2);
			REQUIRE(res.ToDouble() == 10.5);
		}
	}
}

TEST_CASE("*= /=")
{
	WHEN("*=")
	{
		CRational num1(1, 2);
		CRational num2(2, 3);
		num1 *= num2;
		THEN("num1 = 2/6 -> 1/3")
		{
			REQUIRE(num1.GetNumerator() == 1);
			REQUIRE(num1.GetDenominator() == 3);
		}
	}

	WHEN("num += int")
	{
		CRational num(1, 2);
		num *= 3;
		THEN("num = 3/2")
		{
			REQUIRE(num.GetNumerator() == 3);
			REQUIRE(num.GetDenominator() == 2);
		}
	}

	WHEN("/=")
	{
		CRational num1(1, 2);
		CRational num2(2, 3);
		num1 /= num2;
		THEN("num1 = 3/4")
		{
			REQUIRE(num1.GetNumerator() == 3);
			REQUIRE(num1.GetDenominator() == 4);
		}
	}

	WHEN("num /= int")
	{
		CRational num(1, 2);
		num /= 3;
		THEN("num 1/6")
		{
			REQUIRE(num.GetNumerator() == 1);
			REQUIRE(num.GetDenominator() == 6);
		}
	}
}

TEST_CASE("== !=")
{
	WHEN("==")
	{
		CRational num1(1, 2);
		CRational num2(1, 2);
		bool res = (num1 == num2);
		THEN("res = true")
		{
			REQUIRE(res == true);
		}
	}

	WHEN("== int")
	{
		CRational num1(4, 1);
		bool res = (num1 == 4);
		THEN("res = true")
		{
			REQUIRE(res == true);
		}
	}

	WHEN("int ==")
	{
		CRational num1(2, 3);
		bool res = (3 == num1);
		THEN("res = false")
		{
			REQUIRE(res == false);
		}
	}

	WHEN("!=")
	{
		CRational num1(1, 2);
		CRational num2(1, 2);
		bool res = (num1 != num2);
		THEN("res = false")
		{
			REQUIRE(res == false);
		}
	}

	WHEN("!= int")
	{
		CRational num1(1, 2);
		bool res = (num1 != 7);
		THEN("res = true")
		{
			REQUIRE(res == true);
		}
	}

	WHEN("int !=")
	{
		CRational num1(3, 1);
		bool res = (3 != num1);
		THEN("res false")
		{
			REQUIRE(res == false);
		}
	}
}

TEST_CASE("< <= > >=")
{
	WHEN(">=")
	{
		CRational num1(1, 2);
		CRational num2(1, 3);
		bool res = (num1 >= num2);
		THEN("res = true")
		{
			REQUIRE(res == true);
		}
	}

	WHEN("int >=")
	{
		CRational num1(8, 2);
		bool res = (3 >= num1);
		THEN("res = false")
		{
			REQUIRE(res == false);
		}
	}

	WHEN("<=")
	{
		CRational num1(1, 2);
		CRational num2(1, 3);
		bool res = (num1 <= num2);
		THEN("res = false")
		{
			REQUIRE(res == false);
		}
	}

	WHEN("int <=")
	{
		CRational num1(7, 2);
		bool res = (3 <= num1);
		THEN("res = true")
		{
			REQUIRE(res == true);
		}
	}

	WHEN(">")
	{
		CRational num1(3, 1);
		bool res = (num1 > 2);
		THEN("res = true")
		{
			REQUIRE(res == true);
		}
	}

	WHEN("<")
	{
		CRational num1(1, 2);
		bool res = (num1 < 7);
		THEN("res = true")
		{
			REQUIRE(res == true);
		}
	}
}

TEST_CASE("<< >>")
{
	WHEN("<<")
	{
		CRational number(-7, 15);
		std::ostringstream output("");
		output << number;
		THEN("output = -7/15")
		{
			output.str() = "-7/15";
		}
	}

	WHEN(">>")
	{
		CRational number;
		std::istringstream input("7/15");
		input >> number;
		THEN("num = 7, den = 15")
		{
			REQUIRE(number.GetNumerator() == 7);
			REQUIRE(number.GetDenominator() == 15);
		}
	}
}

TEST_CASE("Compound Fraction")
{
	WHEN("positive number")
	{
		CRational number(4, 3);
		std::pair<int, CRational> result = number.ToCompoundFraction();
		THEN("int part = 1, num = 1, den = 3")
		{
			REQUIRE(result.first == 1);
			REQUIRE(result.second.GetNumerator() == 1);
			REQUIRE(result.second.GetDenominator() == 3);
		}
	}

	WHEN("Negative number")
	{
		CRational number(-9, 4);
		std::pair<int, CRational> result = number.ToCompoundFraction();
		THEN("int part = -2, num = -1, den = 4")
		{
			REQUIRE(result.first == -2);
			REQUIRE(result.second.GetNumerator() == -1);
			REQUIRE(result.second.GetDenominator() == 4);
		}
	}

	WHEN("Whole part is not exists")
	{
		CRational number(3, 4);
		std::pair<int, CRational> result = number.ToCompoundFraction();
		THEN("int part = 0, num = 3, den = 4")
		{
			REQUIRE(result.first == 0);
			REQUIRE(result.second.GetNumerator() == 3);
			REQUIRE(result.second.GetDenominator() == 4);
		}
	}
}