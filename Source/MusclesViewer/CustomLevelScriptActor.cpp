// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomLevelScriptActor.h"

void ACustomLevelScriptActor::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Some warning message"));

    APlayerController* MyController = GetWorld()->GetFirstPlayerController();

    MyController->bShowMouseCursor = true;
    MyController->bEnableClickEvents = true;
    MyController->bEnableMouseOverEvents = true;
}

void ACustomLevelScriptActor::ShowBone() {
    UE_LOG(LogTemp, Warning, TEXT("ShowBone"));

    APlayerController* MyController = GetWorld()->GetFirstPlayerController();
    
}