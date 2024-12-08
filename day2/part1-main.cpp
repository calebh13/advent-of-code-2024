#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool evalLine(const string& line)
{
	istringstream stream(line);
	vector<int> v;
	int cur;
	while (stream >> cur) v.push_back(cur);
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
	ifstream infile("input.txt");
	string line;
	int validReportCount = 0;
	while (getline(infile, line))
	{
		if (evalLine(line)) validReportCount++;
	}
	cout << "Valid report count: " << validReportCount << endl;
}
