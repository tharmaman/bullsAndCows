/*
 * This is the console executable, that makes use of the BullCow class
 * This acts as the view in a MVC pattern, and is responsible for all
 * user interaction. For game logic see the FBullCowGame class
 */

// preprocessor directive
#include <iostream>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

// prototypes => contracts
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;     // instantiate a new game


// the entry point of our application
int main()
{
    bool bPlayAgain{false};
    do {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }
    while (bPlayAgain);

    return 0; // exit the application
}


// writing software goal is to manage complexity => future version can see whats up
// Abstraction - considering things at a higher level
// Encapsulation - making sure abstractions are adhered to, and other things can't get ahold of scope

void PrintIntro()
{
    // introduce the game
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    return; // always put return for void as best practice
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
    FText Guess{""};
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do {
        // get a guess from the player
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << ". Enter your guess: ";
        getline(std::cin, Guess);

        // check status and give feedback
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status)
        {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters.\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters.\n";
                break;
            default:
                // assuming guess is valid
                break;
        }
        std::cout << std::endl;
    } while(Status != EGuessStatus::OK); // keep looping until we get no errors
    return Guess;
}

void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();

    // loop asking for guesses while the game
    // is NOT won and there are still tries remaining
    while (!BCGame.isGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        // grabbing a valid guess
        FText Guess = GetValidGuess();

        // submit valid guess to the game and receive counts
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

        // print number of bulls and cows
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
    }

    PrintGameSummary();
    return;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word (y/n)? ";
    FText Response{""};
    getline(std::cin, Response);

    return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
    if (BCGame.isGameWon())
    {
        std::cout << "WELL DONE - YOU WIN!\n";
    } else
    {
        std::cout << "Better luck next time!\n";
    }
}

