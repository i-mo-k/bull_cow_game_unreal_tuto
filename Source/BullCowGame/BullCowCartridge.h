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
		void InitGame();
		void Submit(const FString& Input);
		void EndGame(const FString Message);
		const bool IsIsogram(const FString& Input);

	// Your declarations go below!
	private:
		FString HIDDEN_WORD;
		int32 LIVES;
		bool B_GAME_OVER;
	
};

struct FBullsAndCows 
{
	int32 BullCount = 0;
	int32 CowCount = 0;
};