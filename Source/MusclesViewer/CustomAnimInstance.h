// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "CustomCharacter.h"
#include "C:/Program Files/Epic Games/UE_4.26/Engine/Source/Editor/AnimGraph/Classes/AnimGraphNode_ModifyBone.h"

#include "CustomAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class MUSCLESVIEWER_API UCustomAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
        void InitAnim();

    UPROPERTY(BlueprintReadOnly)
        ACustomCharacter* CustomCharacter;
};
