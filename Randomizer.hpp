#pragma once
#include <random>

class Randomizer
{
public:
	friend int main();
private:
	std::mt19937 generator;

public:
	Randomizer()
	{
		SetSeed();
	}

	int RandomIntRange(int start, int end)
	{
		//range creation
		std::uniform_int_distribution<int> distr(start, end);

		return distr(generator);
	}

	double RandomDoublePercent()
	{
		std::uniform_int_distribution<int> distr(0.0, 1.0);
		return distr(generator);
	}

private:
	void SetSeed()
	{
		std::random_device rd; // obtain a random number from hardware
		generator = std::mt19937(rd());
	}
};

Randomizer RandomGenerator;