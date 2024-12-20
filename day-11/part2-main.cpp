#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#define BLINKS 75
typedef unsigned long long ull;
typedef long long ll;

using namespace std;

inline int calcNumDigits(ull n)
{
	int digits = 0;
	while (n > 0) n /= 10, digits++;
	return digits;
}

inline ull powTen(int p)
{
	int result = 1;
	while (p > 0) result *= 10, p--;
	return result;
}

int main(void)
{
	string line;
	ifstream infile("input.txt");
	getline(infile, line);
	stringstream ss(line);
	unordered_map<ull, ll> rocks;
	rocks.reserve(1000000);
	ull num;
	while (ss >> num) rocks[num]++;

	for (int i = 0; i < BLINKS; i++)
	{
		unordered_map<ull, ll> freqDeltas;
		freqDeltas.reserve(rocks.size() * 3); // avoid resizing during the for loop

		// Work in "chunks", based on the frequency of each number
		for (auto num : rocks)
		{
			if (num.first == 0)
			{
				freqDeltas[0] -= num.second; // Remove n 0s
				freqDeltas[1] += num.second; // Add n 1s
				continue;
			}
			int digits = calcNumDigits(num.first);
			if (digits % 2 == 0)
			{
				ull p = powTen(digits >> 1); // divide by 2 but faster
				freqDeltas[num.first] -= num.second; // Remove original number
				freqDeltas[num.first % p] += (num.second); // Lower digits
				freqDeltas[num.first / p] += (num.second); // Upper digits
			}
			else
			{
				freqDeltas[num.first] -= num.second;
				freqDeltas[num.first * 2024] += num.second;
			}
		}

		for (auto f : freqDeltas)
		{
			rocks[f.first] += f.second;
		}
	}
	
	ll size = 0;
	for (auto n : rocks)
	{
		size += n.second;
	}

	cout << "Total number of rocks: " << size << endl;
}
