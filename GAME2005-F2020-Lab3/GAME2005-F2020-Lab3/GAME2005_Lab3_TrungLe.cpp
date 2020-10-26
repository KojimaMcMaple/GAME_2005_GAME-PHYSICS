#include <iostream>
using namespace std;

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

float RandBetween0And1() {
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

float RandBetween2FloatsWithInterval(float lower_end, float higher_end, float interval) {
	int lowest = lower_end / interval;
	int highest = higher_end / interval;

	return(((rand() % (highest + 1 - lowest)) + lowest) * interval);
}

int main() {
	srand(time(0));

	for (int i = 0; i < 10; i++)
	{
		float temp = RandBetween2FloatsWithInterval(172.8, 1440, 57.6);
		cout << temp;
		cout << "\t= 57.6 * " << temp / 57.6 << endl;
	}

	return 1;
}