// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to the Bull Cows!"));
    PrintLine(TEXT("Press Tab to enter the TERMINAL..."));
    PrintLine(TEXT("Press Enter to continue..."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    FString HiddenWord = TEXT("subdermatoglyphic");
}