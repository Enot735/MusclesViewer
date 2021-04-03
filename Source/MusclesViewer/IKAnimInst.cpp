// Fill out your copyright notice in the Description page of Project Settings.


#include "IKAnimInst.h"

void UIKAnimInst::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    return;
    UE_LOG(LogTemp, Warning, TEXT("Temp Log from NativeInitializeAnimation()"));
    Owner = Cast<AIKPawn>(TryGetPawnOwner());
}

void UIKAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    return;
    //UE_LOG(LogTemp, Warning, TEXT("Temp Log from NativeUpdateAnimation() DeltaSeconds: %f"), DeltaSeconds);
    if (!Owner) {
        UE_LOG(LogTemp, Warning, TEXT("NativeUpdateAnimation: Owner not found!"));
        return;
    }
    UE_LOG(LogTemp, Warning, TEXT("NativeUpdateAnimation: Owner found"));
    //SetHeadTransform(Owner->Camera->GetComponentLocation(), Owner->Camera->GetComponentRotation());
}

void UIKAnimInst::SetHeadTransform(FVector loc, FRotator rot) {

}

