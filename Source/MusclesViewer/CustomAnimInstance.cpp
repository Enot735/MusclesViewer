// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAnimInstance.h"


void UCustomAnimInstance::InitAnim()
{
    APawn* PawnOwner = TryGetPawnOwner();
    if (!IsValid(PawnOwner))
    {
        UE_LOG(LogTemp, Error, TEXT("No PawnOwner"));
        return;
    }

    UE_LOG(LogTemp, Error, TEXT("PawnOwner"));
    CustomCharacter = Cast<ACustomCharacter>(PawnOwner);
}
