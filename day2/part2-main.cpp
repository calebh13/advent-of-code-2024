#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<int> parseLine(const string& line)
{
	istringstream stream(line);
	vector<int> v;
	int cur;
	while (stream >> cur) v.push_back(cur);
	return v;
}

bool evalLine(vector<int> v, int ignoreVal)
{
	if (ignoreVal != -1) v.erase(v.begin() + ignoreVal);
	int diff = v[0] - v[1];
	int minDiff = 0, maxDiff = 0;
	if (diff > 0)
	{
		// Decreasing, so 1 <= [i] - [i+1] <= 3
		minDiff = 1, maxDiff = 3;
	}
	else if (diff < 0)
	{
		// Increasing, so -3 <= [i] - [i+1] <= -1
		minDiff = -3, maxDiff = -1;
	}
	else return false;

	for (int i = 0; i + 1 < v.size(); i++)
	{
			diff = v[i] - v[i + 1];
			if (!(diff >= minDiff && diff <= maxDiff)) return false;
	}
	return true;
}

int main(void)
{
	/*
	First, check if they're equal. If so, unsafe.
	Otherwise, set maxDiff and minDiff based on whether [0] - [1] was increasing or decreasing (pos or neg).
	Repeat this for the entire list.
	*/

	ifstream infile("input.txt");
	string line;
	int validReportCount = 0;
	while (getline(infile, line))
	{
		vector<int> lineNums = parseLine(line);
		for (int ignoreVal = -1; ignoreVal < (int)lineNums.size(); ignoreVal++)
		{
			// First we don't ignore anything, then we try all possible "ignore values" (indices).
			// Unfortunately this is quadratic time, but it avoids checking a ton of edge cases
			// and the dataset isn't large enough for this to cause an issue
			if (evalLine(lineNums, ignoreVal))
			{
				validReportCount++;
				break;
			}
		}
	}
	cout << "Valid report count: " << validReportCount << endl;
}
