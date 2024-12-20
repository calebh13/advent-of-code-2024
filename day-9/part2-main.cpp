#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#define ull unsigned long long
#define LEN 19999 // 19 for example, 19999 for input

using namespace std;

int main(void)
{
	string line;
	line.reserve(LEN);
	ifstream infile("input.txt");
	getline(infile, line);

	/*
	iterate through list, storing the info of all free space positions in a vector.

	then, move right to left in the file map, moving everything into the first available free space 
	(left to right in the vector). set the file to 0 once done, and subtract from the free space as well. 
	add to checksum during insertions.
	
	once this is done, iterate through the list AGAIN, adding up all the file checksums.
	*/

	ull checksum = 0, expandedPos = 0;
	vector<tuple<int, ull, int>> freeSpaces; // stores num of free blocks, expandedPos, and index
	freeSpaces.reserve(LEN / 2);

	for (int i = 0; i+1 < line.length(); i += 2)
	{
		expandedPos += (line[i] - '0'); // skip over file
		int blocks = line[i + 1] - '0';
		if (blocks > 0)
		{
			freeSpaces.push_back(tuple<int, ull, int>(line[i + 1] - '0', expandedPos, i + 1));
			expandedPos += line[i + 1] - '0'; // skip through the free blocks
		}
	}

	// Try to insert rightmost files first
	for (int i = LEN - 1; i >= 0; i -= 2)
	{
		int fileLength = line[i] - '0';
		// Insert into the first available spot, starting from the left
		// And make sure the free space spot is to the left of i
		for (int j = 0; j < freeSpaces.size() && get<2>(freeSpaces[j]) < i; j++)
		{
			// If we have enough space to insert the whole file, do it
			if (get<0>(freeSpaces[j]) >= fileLength)
			{
				for (; fileLength > 0; fileLength--) // insert
				{
					checksum += ((i / 2) * get<1>(freeSpaces[j]));
					get<0>(freeSpaces[j])--; // reduce free space
					get<1>(freeSpaces[j])++; // increment expandedPos for start of the free space
				}
				line[i] -= 10; // hack to show the file has been moved
				break;
			}
		}
	}

	// Now add all the non-moved files
	expandedPos = 0;
	for (int i = 0; i + 1 < line.length(); i += 2)
	{
		if (line[i] < '0') // file was moved
		{
			expandedPos += (line[i] + 10 - '0'); // revert to original value, and add to expandedPos
		}

		for (; line[i] > '0'; line[i]--) // add file to checksum
		{
			checksum += ((i / 2) * expandedPos);
			expandedPos++;
		}

		expandedPos += line[i + 1] - '0'; // add free blocks
	}

	std::cout << "Checksum: " << checksum << endl;
}
