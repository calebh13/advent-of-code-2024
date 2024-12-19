#include <iostream>
#include <fstream>
#include <string>
#define ull unsigned long long
#define LEN 19999 // 19 for example, 19999 for input

using namespace std;

int main(void)
{
	/*
	Conversion process:
	1. Start with "12345"
		- This means 1 file (id 0), 2 free, 3 file (id 1), 4 free, 5 file (id 2)
		- Thus, we have 0..111....22222
		- We want to move from the right to the left.
	2. Get expanded position: start with 0, and add however many file blocks we have: in this case, 1.
	3. Set maxPos to expandedPos + freeSpaceVal. 
	4. While expandedPos < maxPos, "move" values from right to left like so:
		- 022111....222..
		- Each time you add a value, subtract 1 from rightPos, and add 1 to expandedPos (for loop).
	5. Instead of actually moving a value, since expanded string doesn't exist, 
	   multiply the "moved" (right side) ID by expandedPos, and add this character to checksum.
	*/


	string line;
	line.reserve(LEN);
	ifstream infile("input.txt");
	getline(infile, line);

	ull checksum = 0;
	
	int leftId = 0, leftIndex = 0, rightIndex = line.size() - 1;
	ull expandedPos = 0;

	while (leftIndex <= rightIndex)
	{
		// We need to update the checksum, and get to free space.
		// Add up ID * pos:
		ull maxPos = expandedPos + line[leftIndex] - '0';
		while (expandedPos < maxPos)
		{
			checksum += ((leftIndex / 2) * expandedPos); // multiply ID by position
			expandedPos++; // move to next block
		}

		// Instead of doing this, we need to add the files to checksum:
		// Add the number of file blocks, so we are now in free space:
		//cout << "First free spot: index " << expandedPos << endl;

		// Now, add the number of free blocks, so we have to stop BEFORE reaching maxPos:
		// (note that if there is no free space, the for loop won't run and this is ok)
		maxPos = expandedPos + (line[leftIndex + 1] - '0');

		while (expandedPos < maxPos)
		{
			// If we've finished moving the current file, go to the next:
			if (line[rightIndex] == '0')
			{
				rightIndex -= 2;
			}

			// Edge case: this might be the last file, and we don't
			// want to move it onto itself (would add a duplicate to the checksum)
			if (leftIndex >= rightIndex) break; 
			line[rightIndex]--; // "move" file over

			checksum += ((rightIndex / 2) * expandedPos); // multiply ID by position inserted
			expandedPos++; // "insert" file here, and move to next spot
		}

		leftIndex += 2; // move to next file
	}
	std::cout << "Checksum: " << checksum << endl;
}
