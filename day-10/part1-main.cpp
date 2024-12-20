#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#define ROWS 59
#define COLS 59

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

inline bool inBounds(pos cur)
{
	return !(cur.row < 0 || cur.row >= ROWS || cur.col < 0 || cur.col >= COLS);
}

void findNines(const string tab[ROWS], unordered_set<pos, HashFunc>& maxHeightPositions, const pos cur)
{
	if (tab[cur.row][cur.col] == '9')
	{
		maxHeightPositions.insert(cur);
		return;
	}
	else
	{
		char next = tab[cur.row][cur.col] + 1;
		pos up = cur + pos{ -1, 0 }, left = cur + pos{ 0, -1 }, right = cur + pos{ 0, 1 }, down = cur + pos{ 1, 0 };
		if (inBounds(up) && tab[up.row][up.col] == next) findNines(tab, maxHeightPositions, up);
		if (inBounds(left) && tab[left.row][left.col] == next) findNines(tab, maxHeightPositions, left);
		if (inBounds(right) && tab[right.row][right.col] == next) findNines(tab, maxHeightPositions, right);
		if (inBounds(down) && tab[down.row][down.col] == next) findNines(tab, maxHeightPositions, down);
	}
}

int calcScore(const string tab[ROWS], pos trailhead)
{
	unordered_set<pos, HashFunc> maxHeightPositions;
	findNines(tab, maxHeightPositions, trailhead);
	return maxHeightPositions.size(); // finds UNIQUE nines
}

int main(void)
{
	string tab[ROWS];
	ifstream infile("input.txt");
	for (int i = 0; getline(infile, tab[i]); i++);
	int sum = 0;
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (tab[row][col] == '0')
			{
				int score = calcScore(tab, pos{ row, col });
				cout << "Trailhead at " << row << ", " << col << " has a score of " << score << endl;
				sum += score;
			}
		}
	}

	cout << "Sum of all trailheads: " << sum << endl;
}
