// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	virtual TArray<FString> GetValidWords() const;

	private:
	virtual bool CheckGuess(FString Guess);
	virtual void DeductLife();
	virtual void SetupGame();
	virtual void EndGame();
	virtual void ProcessGuess(FString Guess);
	virtual bool IsIsogram(FString Word) const;
	FString HiddenWord;
	int32 PlayerLives;
	bool bGameOver;	
};
