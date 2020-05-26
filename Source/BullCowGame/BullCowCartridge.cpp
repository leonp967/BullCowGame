// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();
    TArray<FString> ValidWords = GetValidWords();
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input)
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Welcome to the Bulls & Cows game!"));

    HiddenWord = TEXT("porta");
    PlayerLives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter isogram!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), PlayerLives);
    PrintLine(TEXT("Press enter to continue..."));
}

bool UBullCowCartridge::CheckGuess(FString Guess)
{
    return Guess.Len() == HiddenWord.Len()
            && IsIsogram(Guess);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for (int32 Index = 0; Index < Word.Len() - 1; Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}

void UBullCowCartridge::DeductLife()
{
    PlayerLives--;
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again..."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess.Equals(HiddenWord))
    {
        ClearScreen();
        PrintLine(TEXT("Congratulations, you have won!"));
        EndGame();
        return;
    }

    if (!CheckGuess(Guess)) {
        PrintLine(TEXT("Your guess is invalid!"));
        PrintLine(TEXT("Tip: your guess has the wrong length \nor has repeating letters."));
        PrintLine(TEXT("Try again!"));
        return;
    }

    DeductLife();

    if (PlayerLives > 0)
    {
        PrintLine(TEXT("Sorry, you guessed wrong!"));
        PrintLine(TEXT("Lives remaining: %i"), PlayerLives);
        PrintLine(TEXT("Try again!"));
        return;
    }

    ClearScreen();
    PrintLine(TEXT("You have lost."));
    PrintLine(TEXT("The word was: %s"), *HiddenWord);
    EndGame();
}

TArray<FString> UBullCowCartridge::GetValidWords() const
{
    TArray<FString> ValidWords;
    for (FString PossibleWord : Words)
    {
        if (PossibleWord.Len() >= 4 && PossibleWord.Len() <= 8 && IsIsogram(PossibleWord))
        {
            ValidWords.Emplace(PossibleWord);
        }
    }
    return ValidWords;
}