// Fill out your copyright notice in the Description page of Project Settings.


#include "IKPawn.h"

// Sets default values
AIKPawn::AIKPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIKPawn::BeginPlay()
{
	Super::BeginPlay();

    MC_Left_Hand = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Left_Hand")));
    MC_Left_Elbow = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Left_Elbow")));
    MC_Left_Shoulder = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Left_Shoulder")));
    
    MC_Left_Foot = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Left_Foot")));
    MC_Left_Knee = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Left_Knee")));
    MC_Left_Thigh = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Left_Thigh")));
    
    MC_Right_Hand = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Right_Hand")));
    MC_Right_Elbow = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Right_Elbow")));
    MC_Right_Shoulder = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Right_Shoulder")));

    MC_Right_Foot = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Right_Foot")));
    MC_Right_Knee = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Right_Knee")));
    MC_Right_Thigh = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Right_Thigh")));

    UE_LOG(LogTemp, Warning, TEXT("Component name: %s"), *MC_Left_Hand->GetName());
}

// Called every frame
void AIKPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (GEngine) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
            FString::Printf(TEXT("MC_Left_Hand: %s;"),
                *MC_Left_Hand->GetComponentLocation().ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
            FString::Printf(TEXT("MC_Left_Elbow: %s;"),
                *MC_Left_Elbow->GetComponentLocation().ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
            FString::Printf(TEXT("MC_Left_Shoulder: %s;"),
                *MC_Left_Shoulder->GetComponentLocation().ToString()));

    }
}

// Called to bind functionality to input
void AIKPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

