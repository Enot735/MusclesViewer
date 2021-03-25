// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Kismet/GameplayStatics.h"
#include "CustomLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class MUSCLESVIEWER_API ACustomLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

	void BeginPlay();

private:
    APlayerController* MyController;
public:
	UFUNCTION(BlueprintCallable)
	void ShowBone();
};