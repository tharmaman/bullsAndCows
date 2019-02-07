//
// Created by Danny Tharma on 2019-02-06.
//

#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { Reset(); }


// const here prevents method from changing any values
// acts as a guard in place
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::isGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
    constexpr int32 MAX_TRIES = 8;
    // constexpr then const if too strong
    const FString HIDDEN_WORD = "planet";

    MyMaxTries = MAX_TRIES;
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (false)  // if the guess isn't an isogram TODO write function
    {
        return EGuessStatus::Not_Isogram;
    } else if (false)   // if the guess isn't all lowercase TODO write function
    {
        return EGuessStatus::Not_Lowercase;
    } else if (Guess.length() != GetHiddenWordLength())   // if the guess length is wrong
    {
        return EGuessStatus::Wrong_Length;
    } else
    {
        return EGuessStatus::OK;
    }
}

// receives a VALID guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = GetHiddenWordLength();   // assuming same length as guess

    // loop through all letters in the guess
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
    {
        // compare letters against the hidden word
        for (int32 GChar = 0; GChar < WordLength; GChar++)
        {
            // if they match then
                if (Guess[GChar] == MyHiddenWord[MHWChar]){
                    if (MHWChar == GChar){    // if they're in the same place
                        BullCowCount.Bulls++;       // increment bulls
                    }
                     else {
                         BullCowCount.Cows++;       // increment cows
                    }
                }
        }
    }
    if (BullCowCount.Bulls == WordLength) {
        bGameIsWon = true;
    } else {
        bGameIsWon = false;
    }

    return BullCowCount;
}

