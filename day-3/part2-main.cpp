#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(void)
{
	ifstream infile("input.txt");
	string line;
	int sum = 0;
	bool enabled = true;
	while (getline(infile, line))
	{
		int i = 0, len = line.length();
		for (; i < len; i++)
		{
			for (; !(line[i] != 'm' || line[i] != 'd') && i < len; i++);
			// i + 4 is so we at least have room for a 'do()'
			if (line[i] == 'd')
			{
				if (i + 3 >= len) continue;
				if (line[i + 1] == 'o' && line[i + 2] == '(' && line[i + 3] == ')')
				{
					enabled = true;
				}
				// don't(): 
				else if (i + 6 < len)
				{
					// because substrings are slow:
					if (line[i + 1] == 'o' && line[i + 2] == 'n' && line[i + 3] == '\''\
						&& line[i + 4] == 't' && line[i + 5] == '(' && line[i + 6] == ')')
					{
						enabled = false;
						i += 6;
						continue;
					}
				}
			}
			
			else if (enabled && line[i] == 'm')
			{
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
	}
	cout << "Sum: " << sum << endl;
}
