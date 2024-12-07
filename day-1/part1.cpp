#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

int main(void)
{
	ifstream infile("input.txt");
	string line;
	// STL min heap
	priority_queue<int, vector<int>, greater<int>> leftQ; 
	priority_queue<int, vector<int>, greater<int>> rightQ;
	while (getline(infile, line))
	{
		leftQ.push(stoi(line.substr(0, 5)));
		rightQ.push(stoi(line.substr(8, 13)));
	}

	int sumOfDifferences = 0;
	
	while (!leftQ.empty() && !rightQ.empty())
	{
		sumOfDifferences += abs(leftQ.top() - rightQ.top());
		leftQ.pop(), rightQ.pop();
	}

	cout << "Sum: " << sumOfDifferences << endl;
}
