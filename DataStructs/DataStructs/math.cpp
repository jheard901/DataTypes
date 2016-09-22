
#include "math.h"
#include <stdlib.h> //srand(), rand()
#include <time.h> //time()

//seed the random number generator with a random value | only need to do once in a program
void SeedGenerator()
{
	srand(unsigned(time(NULL)));
}

//seed the random number generator with a specific value
void SeedGenerator(int seed)
{
	srand(unsigned(seed));
}

//create a random float between 0 - 1
float frn() {
	float randNum = float(rand());
	return randNum / RAND_MAX;
}

//create a random float between a - b
float GetRandomFloat(float a, float b)
{
	if (a >= b) // bad input
		return a;

	return (frn() * (b - a)) + a;
}

//create a random int between a - b | truncates towards 0
int GetRandomInt(float a, float b)
{
	if (a >= b) // bad input
		return a;

	return int((frn() * (b - a)) + a);
}

//create random int between a - b | only works with positive numbers
int GetTrueRandomInt(int a, int b)
{
	if (a >= b)	// bad input
		return a;

	int c = (b - a) + 1;
	return rand() % c + a;
}

