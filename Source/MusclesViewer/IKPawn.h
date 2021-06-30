// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "HTTPService.h"
#include "EngineUtils.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "IKPawn.generated.h"

UCLASS()
class MUSCLESVIEWER_API AIKPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AIKPawn();

    UFUNCTION()
    void OnServerResponseReceived(FString ResponseString);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    AHTTPService *HttpService;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UMotionControllerComponent* Left_Hand;
    UMotionControllerComponent* Left_Elbow;
    UMotionControllerComponent* Left_Shoulder;
    UMotionControllerComponent* Left_Foot;
    UMotionControllerComponent* Left_Knee;
    UMotionControllerComponent* Left_Thigh;

    UMotionControllerComponent* Right_Hand;
    UMotionControllerComponent* Right_Elbow;
    UMotionControllerComponent* Right_Shoulder;
    UMotionControllerComponent* Right_Foot;
    UMotionControllerComponent* Right_Knee;
    UMotionControllerComponent* Right_Thigh;

    UCameraComponent* Camera;

    APawn* Pawn;

protected:

    // Called when the game starts or when spawned
	virtual void BeginPlay() override;

    struct ComponentsFromJson {
        FString NameOfComponent;
        TArray<double> Location[3] = {}, Rotation[3] = {};
    };

    UFUNCTION()
    FString CreateJson();

    // void ParseJsonByJoint(TSharedPtr<FJsonObject> JsonObject, FString NameJoint);

    ComponentsFromJson ParseJoints(TSharedPtr<FJsonObject> JsonObject, TSharedRef<TJsonReader<TCHAR>> Reader, FString NameComponentJson);

    void CreateJsonByComponent(TSharedPtr<FJsonObject> JsonObject, TSharedPtr<FJsonObject> JsonObjectBody, UMotionControllerComponent *Component, FString NameJsonObject);

};