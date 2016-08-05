#pragma once
#include <string>

class FBullCowGame {
public:
	void Reset(); // TODO make a more rich return value;
	int GetMaxTries();
	int GetCurrentTry();
	bool IsGameWon();
	bool CheckGuessValidity(std::string); //TODO make a more rich return value


//Focus on public interface
private:
	int MyCurrentTry;
	int MyMaxTries;
};