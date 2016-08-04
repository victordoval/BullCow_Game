#include <iostream>
#include <string>

using namespace std;

void PrintIntro();
void PlayGame();
string GetGuessAndPrintBack();

int main()
{
	PrintIntro();
	PlayGame();

	return 0; // Exit the application
}

void PlayGame()
{
	// Loop for the number of turns asking for guesses
	constexpr int NUMBER_OF_TURNS = 5;
	for (int count = 1; count <= NUMBER_OF_TURNS; count++)
	{
		string Input = GetGuessAndPrintBack();
		cout << endl;
	}
}

// Introduce the game
void PrintIntro()
{
	constexpr int WORD_LENGTH = 9;
	cout << "Welcome to Bulls and Cows, a fun word game.\n";
	cout << "Can you guess the " << WORD_LENGTH;
	cout << " letter isogram I'm thinking of?\n";
	cout << endl;
}

string GetGuessAndPrintBack()
{
	// Get a guess from the player
	string Guess = "";
	cout << "Enter your guess: ";
	getline(cin, Guess);

	// Repeat the guess back to the player
	cout << "Your guess was: " << Guess << endl;
	return Guess;
}
