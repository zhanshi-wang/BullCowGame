// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord);

    // Welcoming the player
    PrintLine(TEXT("Welcome to the Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess and press Enter to continue..."));

    // Prompt player for guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    // Checking player guess
    // Check if isogram
    // Guess Again
    // Check right number of characters
    // Guess Again

    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You win!"));
        // Play Again?
    }
    else
    {
        if (Input.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("The Hidden Word is %i characters long, try again!"), HiddenWord.Len());
        }
        PrintLine(TEXT("You lose!"));
        // Remove one life
        // If Life <= 0
        // Show game over
        // Play Again?

        // Else
        // Show Life left
        // Guess Again
    }
    
    // If PlayAgain, reset HiddenWord and Life
    // Else quit the game
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("subdermatoglyphic");
    Lives = 4;
}