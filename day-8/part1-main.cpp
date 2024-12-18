#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#define ROWS 50
#define COLS 50

using namespace std;

struct pos
{
	int row;
	int col;

	pos(int row, int col)
	{
		this->row = row;
		this->col = col;
	}

	bool operator==(const pos& p) const
	{
		return (this->row == p.row) && (this->col == p.col);
	}

	pos operator-(const pos& p) const
	{
		return pos{ this->row - p.row, this->col - p.col };
	}

	pos operator+(const pos& p) const
	{
		return pos{ this->row + p.row, this->col + p.col };
	}
};

class HashFunc
{
public:
	size_t operator()(const pos& p) const
	{
		// XOR of predefined hash functions
		return hash<int>()(p.row) ^ hash<int>()(p.col);
	}
};

void printAntennas(const unordered_map<char, vector<pos>>& antennas)
{
	for (auto i : antennas)
	{
		cout << i.first << " locations: ";
		for (auto p : i.second)
		{
			cout << "(" << p.row << "," << p.col << ")" << " ";
		}
		cout << endl;
	}
}

bool inBounds(const pos& p)
{
	return ((p.row >= 0 && p.row < ROWS) && (p.col >= 0 && p.col < COLS));
}

int main(void)
{
	string line[ROWS];
	ifstream infile("input.txt");
	unordered_set<pos, HashFunc> antinodes;
	unordered_map<char, vector<pos>> antennas;
	
	for (int row = 0; getline(infile, line[row]); row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			char c = line[row][col];
			if (c != '.' && c != '#')
			{
				auto iter = antennas.find(c);
				if (iter == antennas.end())
					antennas.insert(pair<char, vector<pos>>(c, vector<pos>{pos{ row, col }}));
				else
					iter->second.push_back(pos{ row, col });
			}
		}
	}

	for (auto a : antennas)
	{
		for (int i = 0; i < a.second.size(); i++)
		{
			pos orig = a.second[i];
			for (int j = i + 1; j < a.second.size(); j++)
			{
				pos delta = a.second[j] - orig;

				pos antinode1 = orig - delta;
				pos antinode2 = a.second[j] + delta;

				if (inBounds(antinode1))
					antinodes.insert(antinode1);

				if (inBounds(antinode2))
					antinodes.insert(antinode2);
			}
		}
	}
	
	cout << "Unique antinodes: " << antinodes.size() << endl;
}
