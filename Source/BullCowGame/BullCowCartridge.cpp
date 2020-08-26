// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    InitGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    if (B_GAME_OVER) {
        InitGame();
    }
    else {
        Submit(Input);
    }
}

void UBullCowCartridge::InitGame() {
    HIDDEN_WORD = TEXT("table");
    LIVES = 3;
    B_GAME_OVER = false;
    ClearScreen();
    PrintLine(TEXT("Welcome to Bulls and Cows game !"));
    PrintLine(TEXT("Press TAB to start guessing."));
    PrintLine(FString::Printf(TEXT("Number of lives left : %d"), LIVES));
}

void UBullCowCartridge::Submit(const FString& Input) {
    int32 InputLength = Input.Len();
    int32 HiddenLength = HIDDEN_WORD.Len();
    if (!IsIsogram(Input)) {
        PrintLine(FString::Printf(TEXT("The word %s is not an isogram.\nEach letter has to appear only once."), *Input));
    }
    else {
        if (InputLength == HiddenLength) {
            PrintLine(Input);
            if (Input == HIDDEN_WORD) {
                EndGame(TEXT("You won !"));
            }
            else {
                FBullsAndCows Count;
                for (int i = 0; i < HIDDEN_WORD.Len(); i++) {
                    TCHAR Letter = Input[i];
                    if (Letter == HIDDEN_WORD[i]) {
                        Count.BullCount++;
                    }
                    else {
                        int32 StartPosition = int32(0);
                        if (HIDDEN_WORD.FindChar(Letter, StartPosition)) {
                            Count.CowCount++;
                        }
                    }
                }
                LIVES--;
                PrintLine(FString::Printf(TEXT("Your word contains %d Bulls and %d Cows."), Count.BullCount, Count.CowCount));
                PrintLine(FString::Printf(TEXT("Number of lives left : %d"), LIVES));
                if (LIVES == 0) {
                    EndGame(TEXT("You lost !"));
                }
            }
        }
        else {
            PrintLine(FString::Printf(TEXT("Input has %d letters, expecting %d"), InputLength, HiddenLength));
            PrintLine(FString::Printf(TEXT("Number of lives left : %d"), LIVES));
        }
    }
}

void UBullCowCartridge::EndGame(const FString Message) {
    PrintLine(Message);
    B_GAME_OVER = true;
    PrintLine(TEXT("Press Enter if you want to play again"));
}

const bool UBullCowCartridge::IsIsogram(const FString& Input) {
    bool bIsIsogram = true;
    for (int i = 0; i < Input.Len() - 1; i++) {
        for (int j = i + 1; j < Input.Len(); j++) {
            if (Input[i] == Input[j]) {
                return false;
            }
        }
    }
    return true;
}