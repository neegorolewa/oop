#pragma once
#include <iostream>
#include <fstream>
#include <iosfwd>
#include <string>
#include <set>

void CheckValidInputStream(const std::string& line, std::ostream& output);

void CheckUpperBoundInRange(int upperBound, std::ostream& output);

void PrintPrimeNumbersSet(const std::set<int>& primesNumber, std::ostream& output);
