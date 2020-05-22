// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();
    SetupGame();
    PrintIntro();
}

void UBullCowCartridge::OnInput(const FString& Input)
{
    ClearScreen();

    if (Input.Equals(HiddenWord))
    {
        PrintLine(TEXT("Congratulations, you guessed right!"));
    }
    else
    {
        DeductLife();
        if (!CheckInput(Input)) {
            PrintLine(TEXT("Your input is incorrect! The word you typed is not an isogram or has the wrong length."));
        }

        if (PlayerLives > 0)
        {
            PrintLine(TEXT("Sorry, you guessed wrong!"));
            PrintLine(TEXT("Lives remaining: %i"), PlayerLives);
        }
        else
        {
            PrintLine(TEXT("You are dead. No lives remaining."));
            PrintLine(TEXT("The word was: %s"), *HiddenWord);
        }
        
    }
}

void UBullCowCartridge::PrintIntro()
{
    PrintLine(TEXT("Welcome to the Bulls & Cows game!"));
    PrintLine(TEXT("Type your guess of the isogram with %i letters..."), HiddenWord.Len());
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("porta");
    PlayerLives = HiddenWord.Len();
}

bool UBullCowCartridge::CheckInput(FString Input)
{
    return Input.Len() == HiddenWord.Len();
}

void UBullCowCartridge::DeductLife()
{
    PlayerLives--;
}