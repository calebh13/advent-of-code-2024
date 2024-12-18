#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define ull unsigned long long
using namespace std;

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
	// if we have 4 numbers, we have 3 operations.
	// so ops ranges from 000 to 111: i.e., 0 to 7
	// highest bit is equal to 2^(3-1)
	int numOps = nums.size() - 1;
	ull cur = nums[0];
	// If we start with multiplication (the highest bit is set), start with 1
	// Move left to right in the binary:
	for (int bitNum = numOps - 1; bitNum >= 0; bitNum--)
	{
		if (ops & (1 << bitNum)) cur *= nums[numOps - bitNum];
		else cur += nums[numOps - bitNum];
	}
	return cur == target;
}

int main(void)
{
	// Use bitwise operations to determine to add or multiply
	// e.g., in a list of 4 numbers, we have a binary number 000
	// that means 3 add operations.
	// 010 means add, multiply, add.
	// note that operators are evaluated left to right, and then the result
	// becomes the left operand in the next operation

	ull sumOfTargets = 0;
	string line;

	ifstream infile("input.txt");
	while (getline(infile, line))
	{
		vector<ull> nums;
		ull target = parseLine(nums, line);
		for (int ops = 0; ops < (1 << (nums.size() - 1)); ops++)
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
