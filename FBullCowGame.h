//
// Created by Danny Tharma on 2019-02-06.
//

#ifndef BULLSCOWS_FBULLCOWGAME_H
#define BULLSCOWS_FBULLCOWGAME_H
#include <string>

// do not use namespace in a header file
using FString = std::string;
using int32 = int;

// two values initialized to zero
struct FBullCowCount
{
    int32 Bulls{0};
    int32 Cows{0};
};

enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};


class FBullCowGame {
public:
    FBullCowGame(); // constructor

    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool isGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;

    void Reset();   // TODO make a more rich return value
    FBullCowCount SubmitValidGuess(FString);     // counts bulls & cows, and increasing try # assuming valid guess


// ^^ Please try and ignore this and focus on interface
private:
    // don't expose variables
    // see constructor for initialization
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
    bool bGameIsWon;

    bool IsIsogram(FString) const;
    bool isLowercase(FString) const;
};

#endif //BULLSCOWS_FBULLCOWGAME_H
