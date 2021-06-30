// Fill out your copyright notice in the Description page of Project Settings.

#include "IKPawn.h"

// Sets default values
AIKPawn::AIKPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

}

// Called when the game starts or when spawned
void AIKPawn::BeginPlay()
{
	Super::BeginPlay();
    
    for (auto h : TActorRange<AHTTPService>(GetWorld()))
        HttpService = h;

    HttpService->OnResponseReceived.AddDynamic(this, &AIKPawn::OnServerResponseReceived);
    
    // Left arm
    Left_Hand = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Left_Hand")));
    Left_Elbow = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Left_Elbow")));
    Left_Shoulder = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Left_Shoulder")));
    
    // Left leg
    Left_Foot = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Left_Foot")));
    Left_Knee = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Left_Knee")));
    Left_Thigh = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Left_Thigh")));
    
    // Right arm
    Right_Hand = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Right_Hand")));
    Right_Elbow = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Right_Elbow")));
    Right_Shoulder = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Right_Shoulder")));
    
    // Right leg
    Right_Foot = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Right_Foot")));
    Right_Knee = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Right_Knee")));
    Right_Thigh = Cast<UMotionControllerComponent>(GetDefaultSubobjectByName(TEXT("MC_Right_Thigh")));
    
    Camera = Cast<UCameraComponent>(GetDefaultSubobjectByName(TEXT("Camera")));
    UE_LOG(LogTemp, Warning, TEXT("Component name: %s"), *Left_Hand->GetName());

}

// Called every frame
void AIKPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FString ContentJsonString = CreateJson();

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpService->PostRequest("/raw_data", ContentJsonString);
    HttpService->Send(Request);

}

// Called to bind functionality to input
void AIKPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AIKPawn::CreateJsonByComponent(
        TSharedPtr<FJsonObject> JsonObject,
        TSharedPtr<FJsonObject> JsonObjectBody,
        UMotionControllerComponent *Component,
        FString NameJsonObject) {

    TArray<TSharedPtr<FJsonValue>> arrLocation;
    
    arrLocation.Add(MakeShareable(new FJsonValueNumber(Component->GetComponentLocation().X)));
    arrLocation.Add(MakeShareable(new FJsonValueNumber(Component->GetComponentLocation().Y)));
    arrLocation.Add(MakeShareable(new FJsonValueNumber(Component->GetComponentLocation().Z)));

    JsonObjectBody->SetArrayField("L", arrLocation);

    TArray<TSharedPtr<FJsonValue>> arrRotation;
    arrRotation.Add(MakeShareable(new FJsonValueNumber(Component->GetComponentRotation().Roll)));
    arrRotation.Add(MakeShareable(new FJsonValueNumber(Component->GetComponentRotation().Pitch)));
    arrRotation.Add(MakeShareable(new FJsonValueNumber(Component->GetComponentRotation().Yaw)));

    JsonObjectBody->SetArrayField("R", arrRotation);

    JsonObject->SetObjectField(NameJsonObject, JsonObjectBody);
    
}

FString AIKPawn::CreateJson() {

    TSharedPtr<FJsonObject> JsonObjectBody = MakeShareable(new FJsonObject);
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

    // LEFT_HAND
    CreateJsonByComponent(JsonObject, JsonObjectBody, Left_Hand, "LEFT_HAND");

    // LEFT_ELBOW 
    JsonObjectBody = MakeShareable(new FJsonObject);
    CreateJsonByComponent(JsonObject, JsonObjectBody, Left_Elbow, "LEFT_ELBOW");

    // LEFT_SHOULDER
    JsonObjectBody = MakeShareable(new FJsonObject);
    CreateJsonByComponent(JsonObject, JsonObjectBody, Left_Shoulder, "LEFT_SHOULDER");

    // LEFT_FOOT
    JsonObjectBody = MakeShareable(new FJsonObject);
    CreateJsonByComponent(JsonObject, JsonObjectBody, Left_Foot, "LEFT_FOOT");

    // LEFT_KNEE
    JsonObjectBody = MakeShareable(new FJsonObject);
    CreateJsonByComponent(JsonObject, JsonObjectBody, Left_Knee, "LEFT_KNEE");

    // LEFT_THIGH
    JsonObjectBody = MakeShareable(new FJsonObject);
    CreateJsonByComponent(JsonObject, JsonObjectBody, Left_Thigh, "LEFT_THIGH");

    // RIGHT_HAND
    JsonObjectBody = MakeShareable(new FJsonObject);
    CreateJsonByComponent(JsonObject, JsonObjectBody, Right_Hand, "RIGHT_HAND");

    // RIGHT_ELBOW 
    JsonObjectBody = MakeShareable(new FJsonObject);
    CreateJsonByComponent(JsonObject, JsonObjectBody, Right_Elbow, "RIGHT_ELBOW");

    // RIGHT_SHOULDER
    JsonObjectBody = MakeShareable(new FJsonObject);
    CreateJsonByComponent(JsonObject, JsonObjectBody, Right_Shoulder, "RIGHT_SHOULDER");

    // RIGHT_FOOT
    JsonObjectBody = MakeShareable(new FJsonObject);
    CreateJsonByComponent(JsonObject, JsonObjectBody, Right_Foot, "RIGHT_FOOT");

    // RIGHT_KNEE
    JsonObjectBody = MakeShareable(new FJsonObject);
    CreateJsonByComponent(JsonObject, JsonObjectBody, Right_Knee, "RIGHT_KNEE");

    // RIGHT_THIGH
    JsonObjectBody = MakeShareable(new FJsonObject);
    CreateJsonByComponent(JsonObject, JsonObjectBody, Right_Thigh, "RIGHT_THIGH");

    FString OutputString;

    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

    UE_LOG(LogTemp, Warning, TEXT("resulting jsonString -> %s"), *OutputString);

    return OutputString;

}

AIKPawn::ComponentsFromJson AIKPawn::ParseJoints(TSharedPtr<FJsonObject> JsonObject, TSharedRef<TJsonReader<TCHAR>> Reader, FString NameComponentJson) {
   
    AIKPawn::ComponentsFromJson Joint;

    Joint.NameOfComponent = NameComponentJson;

    TSharedPtr<FJsonObject> Response = JsonObject->GetObjectField(NameComponentJson);

    TArray<TSharedPtr<FJsonValue>> arrLocation = Response->GetArrayField("L");

    for (auto& obj : arrLocation)
    {
        double value = obj->AsNumber();

        Joint.Location->Add(value);

        UE_LOG(LogTemp, Warning, TEXT("Value = %f"), value);

    }

    TArray<TSharedPtr<FJsonValue>> arrRotation = Response->GetArrayField("R");

    for (auto& obj : arrRotation)
    {
        double value = obj->AsNumber();

        Joint.Rotation->Add(value);

        UE_LOG(LogTemp, Warning, TEXT("Value = %f"), value);

    }

    return Joint;

}

void AIKPawn::OnServerResponseReceived(FString ResponseString) {
    
    TSharedPtr<FJsonObject> JsonObject;
    
    TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(ResponseString);
    
    UE_LOG(LogTemp, Warning, TEXT("Try parse %s"), *ResponseString);

    if (!FJsonSerializer::Deserialize(Reader, JsonObject)) {
        UE_LOG(LogTemp, Warning, TEXT("Cant deserialize response!"));
        return;
    }

    TArray<struct AIKPawn::ComponentsFromJson> ComponentsJson[12] = {};

    // LEFT_HAND
    ComponentsJson[0].Add(ParseJoints(JsonObject, Reader, "LEFT_HAND"));

    // LEFT_ELBOW 
    ComponentsJson[1].Add(ParseJoints(JsonObject, Reader, "LEFT_ELBOW"));

    // LEFT_SHOULDER
    ComponentsJson[2].Add(ParseJoints(JsonObject, Reader, "LEFT_SHOULDER"));

    // LEFT_FOOT
    ComponentsJson[3].Add(ParseJoints(JsonObject, Reader, "LEFT_FOOT"));

    // LEFT_KNEE
    ComponentsJson[4].Add(ParseJoints(JsonObject, Reader, "LEFT_KNEE"));

    // LEFT_THIGH
    ComponentsJson[5].Add(ParseJoints(JsonObject, Reader, "LEFT_THIGH"));

    // RIGHT_HAND
    ComponentsJson[6].Add(ParseJoints(JsonObject, Reader, "RIGHT_HAND"));

    // RIGHT_ELBOW 
    ComponentsJson[7].Add(ParseJoints(JsonObject, Reader, "RIGHT_ELBOW"));

    // RIGHT_SHOULDER
    ComponentsJson[8].Add(ParseJoints(JsonObject, Reader, "RIGHT_SHOULDER"));

    // RIGHT_FOOT
    ComponentsJson[9].Add(ParseJoints(JsonObject, Reader, "RIGHT_FOOT"));

    // RIGHT_KNEE
    ComponentsJson[10].Add(ParseJoints(JsonObject, Reader, "RIGHT_KNEE"));

    // RIGHT_THIGH
    ComponentsJson[11].Add(ParseJoints(JsonObject, Reader, "RIGHT_THIGH"));
    
}