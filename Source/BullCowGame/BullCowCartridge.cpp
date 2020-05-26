// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    Isograms = GetValidWords(Words);
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString &PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
        return;
    }

    ProcessGuess(PlayerInput);
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num())];
    Lives = HiddenWord.Len();
    bGameOver = false;

    // Welcoming the player
    PrintLine(TEXT("Welcome to the Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i Lives."), Lives);
    PrintLine(TEXT("Type in your guess and \nPress Enter to continue..."));
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress Enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
{
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again!\nYou have %i lives remaining."), Lives);
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }

    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You win!"));
        EndGame();
        return;
    }

    PrintLine(TEXT("Lost a life!"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was %s."), *HiddenWord);
        EndGame();
        return;
    }

    // Show the player Bulls and Cows
    FBullCowCount Count = GetBullCows(Guess);
    PrintLine(TEXT("You have %i Bulls and %i Cows"), Count.Bulls, Count.Cows);
    PrintLine(TEXT("Guess again, you have %i lives left."), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString &Word) const
{
    TSet<TCHAR> Appeared;
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        if (Appeared.Contains(Word[Index]))
        {
            return false;
        }
        Appeared.Add(Word[Index]);
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString> &WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString &Guess) const
{
    FBullCowCount Count;

    TSet<TCHAR> Appeared;
    for (int32 Index = 0; Index < Guess.Len(); Index++)
    {
        Appeared.Add(HiddenWord[Index]);
        if (Guess[Index] == HiddenWord[Index])
        {
            Count.Bulls++;
        }
    }

    for (int32 Index = 0; Index < Guess.Len(); Index++)
    {
        if (Guess[Index] != HiddenWord[Index] && Appeared.Contains(Guess[Index]))
        {
            Count.Cows++;
        }
    }

    return Count;
}