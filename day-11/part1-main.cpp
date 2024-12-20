#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#define BLINKS 25
typedef unsigned long long ull;

using namespace std;

int calcNumDigits(ull n)
{
	int digits = 0;
	while (n > 0) n /= 10, digits++;
	return digits;
}

ull powTen(int p)
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
	list<ull> rocks;
	ull num;
	while (ss >> num) rocks.push_back(num);
	for (int i = 0; i < BLINKS; i++)
	{
		for (auto it = rocks.begin(); it != rocks.end(); it++)
		{
			if (*it == 0)
			{
				*it = 1;
				continue;
			}
			int digits = calcNumDigits(*it);
			if (digits % 2 == 0)
			{
				ull p = powTen(digits / 2);
				auto next = it;
				next++;
				rocks.insert(next, *it % p); // right half of digits
				*it /= p; // left half
				it++; // skip recently inserted element
			}
			else
			{
				*it *= 2024;
			}
		}
	}

	cout << "Total number of rocks: " << rocks.size() << endl;
}
