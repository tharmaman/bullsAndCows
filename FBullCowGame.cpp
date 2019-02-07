//
// Created by Danny Tharma on 2019-02-06.
//

#include "FBullCowGame.h"
#include <map>
// preprocessor directive for cut and past (identifier and replacement)
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }


// const here prevents method from changing any values
// acts as a guard in place
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::isGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
    // constexpr then const if too strong
    constexpr int32 MAX_TRIES = 8;
    const FString HIDDEN_WORD = "planet";

    // reinitialize vars
    MyMaxTries = MAX_TRIES;
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bGameIsWon = false;

    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess))  // if the guess isn't an isogram
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (!isLowercase(Guess))   // if the guess isn't all lowercase
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength())   // if the guess length is wrong
    {
        return EGuessStatus::Wrong_Length;
    }
    else
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
    }
    else {
        bGameIsWon = false;
    }

    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    // treat 0 and 1 letter words as isograms
    if (Word.length() <= 1) return true;

    // setup our map
    TMap<char, bool> LetterSeen;

    // its ok to use auto NOT in headers and prototypes
    // for all letters of the word
    for (auto Letter : Word)
    {
        Letter = tolower(Letter);
        // if the letter is in the map
        if (LetterSeen[Letter]){
            return false;  // we do NOT have an isogram
        } else {
            LetterSeen[Letter] = true; // add the letter to the map as seen
        }
    }
    return true;    // for example in cases where /0 is entered
}

bool FBullCowGame::isLowercase(FString Word) const
{
    for (auto Letter: Word)
    {
        if (!islower(Letter))
        {
            return false;
        }
    }
    return false;
}

