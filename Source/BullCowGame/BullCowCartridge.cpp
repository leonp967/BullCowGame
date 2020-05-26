// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();
    Isograms = GetValidWords(Words);
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

    int32 RandomIndex = FMath::RandRange(0, Isograms.Num() - 1);
    HiddenWord = Isograms[RandomIndex];
    PlayerLives = HiddenWord.Len() * 2;
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter isogram!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), PlayerLives);
    PrintLine(TEXT("Press enter to continue..."));
    PrintLine(TEXT("The word is: %s"), *HiddenWord); //Debug
}

bool UBullCowCartridge::CheckGuess(const FString& Guess)
{
    return Guess.Len() == HiddenWord.Len()
            && IsIsogram(Guess);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
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

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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
        FBullCowCount Count = GetBullCows(Guess);

        PrintLine(TEXT("Sorry, you lost a life!"));
        PrintLine(TEXT("You have %i Bulls and %i Cows"), Count.Bulls, Count.Cows);
        PrintLine(TEXT("Lives remaining: %i"), PlayerLives);
        PrintLine(TEXT("Try again!"));
        return;
    }

    ClearScreen();
    PrintLine(TEXT("You have lost."));
    PrintLine(TEXT("The word was: %s"), *HiddenWord);
    EndGame();
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    for (FString PossibleWord : WordList)
    {
        if (PossibleWord.Len() >= 4 && PossibleWord.Len() <= 8 && IsIsogram(PossibleWord))
        {
            ValidWords.Emplace(PossibleWord);
        }
    }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 Index = 0; Index < Guess.Len(); Index++)
    {
        int32 IndexFound;
        if (HiddenWord.FindChar(Guess[Index], IndexFound))
        {
            if (IndexFound == Index)
            {
                Count.Bulls++;
            }
            else
            {
                Count.Cows++;
            }
        }
    }
    return Count;
}