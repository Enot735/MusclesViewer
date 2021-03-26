// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacter.h"

// Sets default values
ACustomCharacter::ACustomCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACustomCharacter::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Begin Play"));

    MyController = UGameplayStatics::GetPlayerController(this, 0);

    MyController->bShowMouseCursor = true;
    MyController->bEnableClickEvents = true;
    MyController->bEnableMouseOverEvents = true;
}

// Called every frame
void ACustomCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACustomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//Called to get Bone Name and Location
void ACustomCharacter::ShowBone() {
    FHitResult Hit;
    MyController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery2, true, Hit);
    UE_LOG(LogTemp, Warning, TEXT("Controller: %s, ShowBone: %s"), *MyController->GetFName().ToString(), *Hit.BoneName.ToString());
}
