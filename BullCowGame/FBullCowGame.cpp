#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5},{4,5},{5,6},{6,8},{7,15} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;	// TODO write function
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase
	{	
		return EGuessStatus::Not_Lowercase; // TODO write function
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a valid guess, increments turn, and returns count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming the same length as guess

	// loop through all letters in the hidden word
	for (int32 GChar = 0; GChar < WordLength; GChar++) {
		// compare letters against the hidden word
		for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (GChar == MHWChar) { // if they're in the same place
					BullCowCount.Bulls++; // increment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;			// setup our map

	// loop through letters in the word
	for (auto Letter : Word) {				// for all letters of the word
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {			// if the letter is in map
			return false;						// we do NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true;		// add the letter to map as seen
		}
	}
	return true;							// for example in cases where \0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	for (auto Letter : Word) {
		if (!islower(Letter)) {				// if the letter is NOT lowercase
			return false;
		}
	}
	return true;
}
