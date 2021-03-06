/* This is the console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <Windows.h>

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void ResizeConsole();
void ClearScreen();
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

int32 main()
{
	ResizeConsole(); // resizes console window for the ASCII art to fit

	do {
		ClearScreen();
		PrintIntro();
		PlayGame();
	} 
	while (AskToPlayAgain());

	return 0; // exit the application
}

void ResizeConsole()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console, 0, 0, 600, 700, TRUE);
	return;
}

void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void PrintIntro()
{
	std::cout << std::endl;
	std::cout << "                           /|                        /|\n";
	std::cout << "                           | \\           __ _ _     / ;\n";
	std::cout << "                     ___    \\ \\   _.-\"-\" `~\"\\  `\"--' /\n";
	std::cout << "                 _.-'   \"\"-._\\ \"\"   ._,\"  ; \"\\\"--._./\n";
	std::cout << "             _.-'       \\./    \"-\"\"\", )  ~\"  |\n";
	std::cout << "            / ,- .'          ,     '  `o.  ;  )\n";
	std::cout << "            \\ ;/       '                 ;   /\n";
	std::cout << "             |/        '      |      \\   '   |\n";
	std::cout << "             /        |             J.\"\\  ,  |\n";
	std::cout << "            \"         :       \\   .'  : | ,. _)\n";
	std::cout << "            |         |     /     f |  |`--\"--'\n";
	std::cout << "             \\_        \\    \\    / _/  |\n";
	std::cout << "              \\ \"-._  _.|   (   j/; -'/\n";
	std::cout << "               \\  | \"/  (   |   /,    |\n";
	std::cout << "                | \\  |  /\\  |\\_///   /\n";
	std::cout << "                \\ /   \\ | \\  \\  /   /\n";
	std::cout << "                 ||    \\ \\|  |  |  |\n";
	std::cout << "                 ||     \\ \\  |  | /\n";
	std::cout << "                 |\\      |_|/   ||\n";
	std::cout << "                 L \\       ||   ||\n";
	std::cout << "                 `\"'       |\\   |\\\n";
	std::cout << "                           ( \\. \\ `.\n";
	std::cout << "                           |_ _\\|_ _\\\n";
	std::cout << "                             \"    \"\n";

	std::cout << "  ____        _ _                       _    _____\n";
	std::cout << " |  _ \\      | | |                     | |  / ____|\n";
	std::cout << " | |_) |_   _| | |___    __ _ _ __   __| | | |     _____      _____\n";
	std::cout << " |  _ <| | | | | / __|  / _` | '_ \\ / _` | | |    / _ \\ \\ /\\ / / __|\n";
	std::cout << " | |_) | |_| | | \\__ \\ | (_| | | | | (_| | | |___| (_) \\ V  V /\\__ \\\n";
	std::cout << " |____/ \\__,_|_|_|___/  \\__,_|_| |_|\\__,_|  \\_____\\___/ \\_/\\_/ |___/\n";

	std::cout << "\n\n             Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "         Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and receive count
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();

	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		default:
			// assume we've exhausted all cases
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again using the same hidden word [y/n]? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'Y') || (Response[0] == 'y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else {
		std::cout << "Better luck next time!\n";
	}
	return;
}
