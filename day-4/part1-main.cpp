#include <iostream>
#include <fstream>
#include <string>
#define LINES 140
#define LEN 140
using namespace std;

int main(void)
{
	ifstream infile("input.txt");
	string tab[LINES];
	int count = 0;

	for (int i = 0; getline(infile, tab[i]); i++);
	
	for (int i = 0; i < LINES; i++)
	{
		for (int j = 0; j < LEN; j++)
		{
			if (tab[i][j] != 'X') continue;
			for (int rowInc = -1; rowInc <= 1; rowInc++)
			{
				if (i + rowInc * 3 < 0) continue;
				if (i + rowInc * 3 >= LINES) break;

				for (int colInc = -1; colInc <= 1; colInc++)
				{
					if (j + colInc * 3 < 0) continue;
					if (j + colInc * 3 >= LEN) break;

					if (tab[i + rowInc][j + colInc] != 'M') continue;
					if (tab[i + rowInc * 2][j + colInc * 2] != 'A') continue;
					if (tab[i + rowInc * 3][j + colInc * 3] != 'S') continue;
					count++;
				}
			}
		}
	}
	
	cout << "Count: " << count << endl;
}
