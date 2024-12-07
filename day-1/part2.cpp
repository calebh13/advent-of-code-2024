#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

int main(void)
{
	ifstream infile("input.txt");
	string line;
	vector<int> leftList;
	unordered_map<int, int> rightFreqTable;
	
	while (getline(infile, line))
	{
		// Build left list
		leftList.push_back(stoi(line.substr(0, 5)));

		// Now build frequency table
		int cur = stoi(line.substr(8, 13));
		auto freq = rightFreqTable.find(cur);
		if (freq == rightFreqTable.end())
		{
			rightFreqTable.insert(std::pair<int, int>(cur, 1));
		}
		else
		{
			freq->second++; // increase frequency
		}
	}

	int similaritySum = 0;

	for (int i : leftList)
	{

		auto freq = rightFreqTable.find(i);
		if (freq != rightFreqTable.end())
			similaritySum += (i * freq->second);
	}

	cout << "Similarity score: " << similaritySum << endl;
}
