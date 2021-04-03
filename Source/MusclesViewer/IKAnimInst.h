// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IKPawn.h"
#include "IKAnimInst.generated.h"

/**
 * 
 */
UCLASS()
class MUSCLESVIEWER_API UIKAnimInst : public UAnimInstance
{
    GENERATED_BODY()

    /*virtual void BlueprintBeginPlay() override;
    virtual void BlueprintUpdateAnimation(float DeltaTimeX) override;*/
public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    void SetHeadTransform(FVector loc, FRotator rot);
private:
    AIKPawn* Owner;
};
