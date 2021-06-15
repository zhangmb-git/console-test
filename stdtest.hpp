#pragma once
#include <random>
#include <iostream>
#include <time.h>
using namespace  std;

void testRandom() {
	int min = 0;
	int max = 100;
	default_random_engine e(static_cast<unsigned int>(time(nullptr)));
	std::uniform_int_distribution<> u(min, max);
	for (int i = 0; i < 10; i++)
	{
		std::cout << u(e) << endl;
	}
	


}