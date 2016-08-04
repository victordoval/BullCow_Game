#include <iostream>
#include <string>

using namespace std;

void PrintIntro();
void PlayGame();
string GetGuess();
bool AskToPlayAgain();

int main()
{
	PrintIntro();
	PlayGame();
	AskToPlayAgain();
	

	return 0; // Exit the application
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

void PlayGame()
{
	// Loop for the number of turns asking for guesses
	constexpr int NUMBER_OF_TURNS = 5;
	for (int count = 1; count <= NUMBER_OF_TURNS; count++)
	{
		string Input = GetGuess();
		cout << "Your guess was: " << Input << endl;
		cout << endl;
	}
}

string GetGuess()
{
	// Get a guess from the player
	string Guess = "";
	cout << "Enter your guess: ";
	getline(cin, Guess);

	return Guess;
}

bool AskToPlayAgain()
{
	cout << "Do you want to play again? ";
	string Response = "";
	getline(cin, Response);
	return (Response[0] == 'Y') || (Response[0] == 'y');
}
