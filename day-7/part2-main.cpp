#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#define ull unsigned long long
using namespace std;

ull concatenate(ull x, ull y) {
	ull pow = 10;
	while (y >= pow)
		pow *= 10;
	return x * pow + y;
}

// Returns target
ull parseLine(vector<ull>& nums, const string& line)
{
	stringstream ss(line);
	string temp;
	ull num, target;

	getline(ss, temp, ':');
	target = stoull(temp);
	while (ss >> num) nums.push_back(num);
	return target;
}

bool matchesTarget(const vector<ull>& nums, ull target, int ops)
{
	int numOps = nums.size() - 1;
	ull cur = nums[0];
	// Move right to left in the ternary
	for (int bitNum = numOps - 1; bitNum >= 0; bitNum--)
	{
		int op = ops % 3;
		ops /= 3;
		if (op == 0) cur += nums[numOps - bitNum];
		else if (op == 1) cur *= nums[numOps - bitNum];
		else cur = concatenate(cur, nums[numOps - bitNum]);
	}
	return cur == target;
}

int main(void)
{
	ull sumOfTargets = 0;
	string line;

	ifstream infile("input.txt");
	for (int i = 0; getline(infile, line); i++)
	{
		vector<ull> nums;
		ull target = parseLine(nums, line);
		int maxOps = (int)pow(3, nums.size() - 1);
		for (int ops = 0; ops < maxOps; ops++)
		{
			if (matchesTarget(nums, target, ops))
			{
				sumOfTargets += target;
				break;
			}
		}
	}
	
	cout << "Sum of targets: " << sumOfTargets << endl;
}
