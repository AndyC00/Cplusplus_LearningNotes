#include <iostream>
#include <cstdlib>

using namespace std;

void move(char input, int& x, int& y);
void checkTreasure(int x, int y);

int main()
{
	//initialise
	int x = 0, y = 0;
	char input;

	//start
	cout << "Find the hidden treasure!" << endl;
	cout << "-------------------------\n\n" << "Press 'Q' to quit at any time...\n" << endl;
	
	while (1)
	{
		cout << "You are at (" << x << ", " << y << ").Move(N / E / S / W)?" << endl;

		//read input
		cin >> input;
		input = tolower(input);

		if (input == 'q' || input == 'Q')
		{
			break;
		}
		else
		{
			move(input, x, y);
			checkTreasure(x, y);
		}
	}

	return 0;
}

void move(char input, int& x, int& y)
{
	switch (input) 
	{
		case 'n':
			if (y < 10)
			{
				y++;
				break;
			}
			else
			{
				cout << "+-----------------------------------------+\n| You have reached the edge of the world!|\n+-----------------------------------------+" << endl;
				break;
			}
		case 'N':
			if (y < 10)
			{
				y++;
				break;
			}
			else
			{
				cout << "+-----------------------------------------+\n| You have reached the edge of the world!|\n+-----------------------------------------+" << endl;
				break;
			}
		case 'e':
			if (x < 10)
			{
				x++;
				break;
			}
			else
			{
				cout << "+-----------------------------------------+\n| You have reached the edge of the world!|\n+-----------------------------------------+" << endl;
				break;
			}
		case 'E':
			if (x < 10)
			{
				x++;
				break;
			}
			else
			{
				cout << "+-----------------------------------------+\n| You have reached the edge of the world!|\n+-----------------------------------------+" << endl;
				break;
			}
		case 's':
			if (y > -10)
			{
				y--;
				break;
			}
			else
			{
				cout << "+-----------------------------------------+\n| You have reached the edge of the world!|\n+-----------------------------------------+" << endl;
				break;
			}
		case 'S':
			if (y > -10)
			{
				y--;
				break;
			}
			else
			{
				cout << "+-----------------------------------------+\n| You have reached the edge of the world!|\n+-----------------------------------------+" << endl;
				break;
			}
		case 'w':
			if (x > -10)
			{
				x--;
				break;
			}
			else
			{
				cout << "+-----------------------------------------+\n| You have reached the edge of the world!|\n+-----------------------------------------+" << endl;
				break;
			}
		case 'W':
			if (x > -10)
			{
				x--;
				break;
			}
			else
			{
				cout << "+-----------------------------------------+\n| You have reached the edge of the world!|\n+-----------------------------------------+" << endl;
				break;
			}
		default:
			cout << "Invalid move. Use N, E, S, or W." << endl;
	}
}

void checkTreasure(int x, int y)
{
	pair<int, int> location (x,y);
	pair<int, int> Pirate (2, 3);
	pair<int, int> Golden(-5, -3);
	pair<int, int> Gemstones(1, -2);
	pair<int, int> Artwork(5, 2);
	pair<int, int> Sword(7, 7);

	if (location == Pirate)
	{
		cout << "*******************************\n* You found a pirate's chest! *\n*******************************" << endl;
	}
	else if (location == Golden)
	{
		cout << "*******************************\n* You found a Golden idol! *\n*******************************" << endl;
	}
	else if (location == Gemstones)
	{
		cout << "*******************************\n* You found a Precious gemstones! *\n*******************************" << endl;
	}
	else if (location == Artwork)
	{
		cout << "*******************************\n* You found a Lost artwork! *\n*******************************" << endl;
	}
	else if (location == Sword)
	{
		cout << "*******************************\n* You found a Holy sword! *\n*******************************" << endl;
	}
}