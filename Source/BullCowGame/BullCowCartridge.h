// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	virtual TArray<FString> GetValidWords(const TArray<FString>& WordList) const;
	virtual bool IsIsogram(const FString& Word) const;
	virtual FBullCowCount GetBullCows(const FString& Guess) const;

	private:
	virtual bool CheckGuess(const FString& Guess);
	virtual void DeductLife();
	virtual void SetupGame();
	virtual void EndGame();
	virtual void ProcessGuess(const FString& Guess);
	FString HiddenWord;
	int32 PlayerLives;
	bool bGameOver;	
	TArray<FString> Isograms;
};
