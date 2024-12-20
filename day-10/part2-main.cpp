#include <iostream>
#include <fstream>
#include <string>
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

	pos operator+(const pos& p) const
	{
		return pos{ this->row + p.row, this->col + p.col };
	}
};

inline bool inBounds(pos cur)
{
	return !(cur.row < 0 || cur.row >= ROWS || cur.col < 0 || cur.col >= COLS);
}

int findNines(const string tab[ROWS], const pos cur)
{
	int sum = 0;
	if (tab[cur.row][cur.col] == '9')
	{
		return 1;
	}
	else
	{
		char next = tab[cur.row][cur.col] + 1;
		pos up = cur + pos{ -1, 0 }, left = cur + pos{ 0, -1 }, right = cur + pos{ 0, 1 }, down = cur + pos{ 1, 0 };
		if (inBounds(up) && tab[up.row][up.col] == next) sum += findNines(tab, up);
		if (inBounds(left) && tab[left.row][left.col] == next) sum += findNines(tab, left);
		if (inBounds(right) && tab[right.row][right.col] == next) sum += findNines(tab, right);
		if (inBounds(down) && tab[down.row][down.col] == next) sum += findNines(tab, down);
	}
	return sum;
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
				int rating = findNines(tab, pos{ row, col });
				cout << "Trailhead at " << row << ", " << col << " has a rating of " << rating << endl;
				sum += rating;
			}
		}
	}

	cout << "Sum of all trailheads: " << sum << endl;
}
