#pragma once
#include <iostream>

struct Sportsman
{
	std::string name;
	int height;
	int weight;
};

bool CompareHeight(const Sportsman& first, const Sportsman& second);
bool CompareWeight(const Sportsman& first, const Sportsman& second);