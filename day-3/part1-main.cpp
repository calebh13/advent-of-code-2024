#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(void)
{
	ifstream infile("input.txt");
	string line;
	int sum = 0;
	while (getline(infile, line))
	{
		size_t i = 0, len = line.length();
		for (; i < len; i++)
		{
			for (; line[i] != 'm' && i < len; i++);
			// We're now at an 'm', or the end of the string
			if (i + 7 >= len) break; // we need at LEAST length for "ul(1,1)"
			if (line[i + 1] == 'u' && line[i + 2] == 'l' && line[i + 3] == '(' && isdigit(line[i + 4]))
			{
				// Now, we have to ensure we have numbers:
				string numstr;
				for (i += 4; isdigit(line[i]) && i < len; i++)
				{
					numstr += line[i];
				}
				int x = stoi(numstr);
				numstr.clear();
				// we now have our first number, so let's get the second:
				if (line[i] != ',' || i >= len) continue;
				for (i += 1; isdigit(line[i]) && i < len; i++)
				{
					numstr += line[i];
				}
				int y = stoi(numstr);
				if (i < len && line[i] == ')')
				{
					sum += x * y;
				}
			}
		}
	}
	cout << "Sum: " << sum << endl;
}
