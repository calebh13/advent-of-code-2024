#include <iostream>
#include <fstream>
#include <string>
#define LINES 130 // 130
#define LEN 130 // 130
#define STARTROW 49 // 49
#define STARTCOL 47 // 47
using namespace std;

enum dir {UP, DOWN, LEFT, RIGHT};

int main(void)
{
	ifstream infile("input.txt");
	string grid[LINES];
	int count = 0;
	int row = STARTROW, col = STARTCOL; // hardcoded starting position
	dir d = UP; // hardcoded direction (reflected in line below)
	int rowInc = -1, colInc = 0;

	for (int i = 0; getline(infile, grid[i]); i++);

	// Now we replace everything with X's, while we're in the map bounds
	while ((row >= 0 && row < LINES) && (col >= 0 && col < LINES))
	{
		if (grid[row][col] == '#')
		{
			// Move back and rotate 90 degrees
			row -= rowInc, col -= colInc;
			switch (d)
			{
			case UP:
				d = RIGHT;
				rowInc = 0, colInc = 1;
				break;
			case RIGHT:
				d = DOWN;
				rowInc = 1, colInc = 0;
				break;
			case LEFT:
				d = UP;
				rowInc = -1, colInc = 0;
				break;
			case DOWN:
				d = LEFT;
				rowInc = 0, colInc = -1;
				break;
			}
		}
		if (grid[row][col] != 'X')
		{
			grid[row][col] = 'X';
			count++;
		}
		row += rowInc, col += colInc;
	}
	

	std::cout << "Count: " << count << "\n";
}
