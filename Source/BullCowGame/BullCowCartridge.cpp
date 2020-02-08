// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    if (bGameOver)
    {
        SetupGame();
        return;
    }

    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug

    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You win!"));
        EndGame();
    }
    else
    {
        if (Input.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("The Hidden Word is %i characters long, try again!"), HiddenWord.Len());
        }
        PrintLine(TEXT("You lose!"));
        if (--Lives <= 0)
        {
            PrintLine(TEXT("Game Over!"));
            EndGame();
        }
        else
        {
            PrintLine(TEXT("You have %i lives left."), Lives);
        }
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("subdermatoglyphic");
    Lives = 4;
    bGameOver = false;

    // Welcoming the player
    PrintLine(TEXT("Welcome to the Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess.\nPress Enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play again."));
}