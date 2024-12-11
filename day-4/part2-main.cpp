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
	
	// Bounds adjustment in for loop helps us avoid bounds checking in if statements
	for (int i = 1; i < LINES - 1; i++)
	{
		for (int j = 1; j < LEN - 1; j++)
		{
			if (tab[i][j] != 'A') continue;
			// If top left is M or S:
			if ((tab[i-1][j-1] == 'M' || tab[i-1][j-1] == 'S'))
			{
				// And across from it is the other:
				if ((tab[i + 1][j + 1] == 'M' || tab[i + 1][j + 1] == 'S')\
					&& tab[i + 1][j + 1] != tab[i - 1][j - 1])
				{
					// If top right is M or S:
					if (tab[i - 1][j + 1] == 'M' || tab[i - 1][j + 1] == 'S')
					{
						// And across from it is the other:
						if ((tab[i + 1][j - 1] == 'M' || tab[i + 1][j - 1] == 'S')\
							&& tab[i + 1][j - 1] != tab[i - 1][j + 1])
						{
							count++;
						}
					}
				}
			}
		}
	}
	std::cout << "Count: " << count << endl;
}
