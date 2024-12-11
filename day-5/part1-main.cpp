#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

vector<int> parseLine(string line)
{
	vector<int> v((line.length() + 1) / 3);
	for (int i = 0; i < v.size(); i++)
	{
		v[i] = 10 * (line[i * 3] - '0') + line[i * 3 + 1] - '0';
	}
	return v;
}

int main(void)
{
	ifstream infile("input.txt");
	string line;
	// the unordered_set contains the pages that must be before that map entry's key
	unordered_map<int, unordered_set<int>> rules;
	int sum = 0;

	while (getline(infile, line) && line != "")
	{
		// All x and y are 2-digit numbers
		int x = 10 * (line[0] - '0') + (line[1] - '0');
		int y = 10 * (line[3] - '0') + (line[4] - '0');
		auto iter = rules.find(y);
		if (iter == rules.end())
			rules.insert(std::pair<int, unordered_set<int>>(y, { x }));
		else
			iter->second.insert(x);
	}

	for (int lineNum = 0; getline(infile, line); lineNum++)
	{
		vector<int> nums = parseLine(line);
		unordered_set<int> seenNums, illegalNums;
		bool correct = true;
		for (int i = 0; i < nums.size(); i++)
		{
			if (illegalNums.find(nums[i]) != illegalNums.end())
			{
				// This means we've found a page that has to come before something to the left.
				correct = false;
				break;
			}

			auto numIter = rules.find(nums[i]);
			if (numIter != rules.end())
			{
				// For each required page, if we haven't seen it, add it to illegalNums: the required pages can't appear now, otherwise list is invalid
				for (auto req : numIter->second)
				{
					if (seenNums.find(req) == seenNums.end())
						illegalNums.insert(req);
				}
			}
			seenNums.insert(nums[i]);
		}
		// if we've reached this, every number is valid
		// we need to now add up the middle page number:
		if(correct) sum += (nums[nums.size() / 2]);
	}

	std::cout << "Sum: " << sum << "\n";
}














