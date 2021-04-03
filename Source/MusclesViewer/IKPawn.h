// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "IKPawn.generated.h"

UCLASS()
class MUSCLESVIEWER_API AIKPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AIKPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    UMotionControllerComponent *MC_Left_Hand;
    UMotionControllerComponent *MC_Left_Elbow;
    UMotionControllerComponent *MC_Left_Shoulder;
    UMotionControllerComponent *MC_Left_Foot;
    UMotionControllerComponent *MC_Left_Knee;
    UMotionControllerComponent *MC_Left_Thigh;

    UMotionControllerComponent *MC_Right_Hand;
    UMotionControllerComponent *MC_Right_Elbow;
    UMotionControllerComponent *MC_Right_Shoulder;
    UMotionControllerComponent *MC_Right_Foot;
    UMotionControllerComponent *MC_Right_Knee;
    UMotionControllerComponent *MC_Right_Thigh;

    UCameraComponent *Camera;
};
