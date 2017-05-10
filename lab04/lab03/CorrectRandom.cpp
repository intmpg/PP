#include "CorrectRandom.h"

float RandomRangeFloat(float a, float b)
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, int(b));
	return dist(gen);
}

template <typename T>
std::string NumberToString(T number)
{
	std::ostringstream os;
	os << number;
	return os.str();

}