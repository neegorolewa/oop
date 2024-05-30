#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template < typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	auto maxElementIt = std::max_element(arr.begin(), arr.end(), less);

	if (maxElementIt == arr.end())
	{
		return false;
	}

	maxValue = *maxElementIt;
	return true;
}