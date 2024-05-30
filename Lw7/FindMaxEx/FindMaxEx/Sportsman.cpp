#include "Sportsman.h"
#pragma once

bool CompareHeight(const Sportsman& first, const Sportsman& second)
{
	return first.height < second.height;
}

bool CompareWeight(const Sportsman& first, const Sportsman& second)
{
	return first.weight < second.weight;
}
