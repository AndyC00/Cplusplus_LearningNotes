#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	cout << "BUZZ, HUM, ZAP... Powering up the AI-Bot...\nAI: Welcome to ""The 'Basic' Letter Guessing Game""!" << endl;
	
	srand(int(time(0)));

	char Letters[30] = "abcdefghijklmnopqrstuvwxyz";
	char input;
	char quit;
	int round = 1;

	while (1)
	{
		//select the secret number
		int select = rand() % 26;
		Letters[select] = toupper(Letters[select]);

		cout << "AI: Here we go! ...";
		for (int i = 0; i < 26; i++)
		{
			cout << Letters[i];
		}
		cout << "...\nAI: I'm thinking of a secret letter, can you guess it...\n" << endl;

		//start guessing
		while (1)
		{
			cout << "\tAI: Turn " << round << ", what is your guess ? \n" << endl;
			cin >> input;
			cout << "Human: " << input << "\n" << endl;

			//checking the answer
			if (input != Letters[select] && input != tolower(Letters[select]))
			{
				input = toupper(input);

				if (input < Letters[select])
				{
					cout << "AI: Wrong... my secret letter comes before " << input << " in the alphabet...\n" << endl;
				}
				else if (input > Letters[select])
				{
					cout << "AI: Wrong... my secret letter comes after " << input << " in the alphabet...\n" << endl;
				}
			}
			else
			{
				break;
			}
			round++;
		}
		
		cout << "\tAI: Well done!\n";
		cout << "\tAI: You took "<< round <<" turns!Game over!\n";
		cout << "\tAI : Play again(y / n) ?\n";
		
		//check if player want to quit
		cin >> quit;
		if (quit == 'n' || quit == 'N')
		{
			break;
		}

		//reset the selecting letter
		Letters[select] = tolower(Letters[select]);
	}

	cout << "thanks for playing!" << endl;

	return 0;
}