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

    for (auto h : TActorRange<AHTTPService>(GetWorld()))
        HttpService = h;

    HttpService->OnResponseReceived.AddDynamic(this, &AIKPawn::OnBotResponseReceived);

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
    
    Camera = Cast<UCameraComponent>(GetDefaultSubobjectByName(TEXT("Camera")));
    UE_LOG(LogTemp, Warning, TEXT("Component name: %s"), *MC_Left_Hand->GetName());

}

void AIKPawn::getLocationRotationOfComponent(TSharedPtr<FJsonObject> JsonObject, UMotionControllerComponent *Component) {

    TArray<TSharedPtr<FJsonValue>> arrLocation;
    
    UE_LOG(LogTemp, Warning, TEXT("Component name: %s"), Component->GetName());

    arrLocation.Add(MakeShareable(new FJsonValueNumber(Component->GetComponentLocation().X)));
    arrLocation.Add(MakeShareable(new FJsonValueNumber(Component->GetComponentLocation().Y)));
    arrLocation.Add(MakeShareable(new FJsonValueNumber(Component->GetComponentLocation().Z)));

    JsonObject->SetArrayField("L", arrLocation);

    TArray<TSharedPtr<FJsonValue>> arrRotation;
    arrRotation.Add(MakeShareable(new FJsonValueNumber(Component->GetComponentRotation().Roll)));
    arrRotation.Add(MakeShareable(new FJsonValueNumber(Component->GetComponentRotation().Pitch)));
    arrRotation.Add(MakeShareable(new FJsonValueNumber(Component->GetComponentRotation().Yaw)));

    JsonObject->SetArrayField("R", arrRotation);

}

FString AIKPawn::createJson() {

    TSharedPtr<FJsonObject> JsonObjectBody = MakeShareable(new FJsonObject);
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

    // LEFT_ELBOW 
    getLocationRotationOfComponent(JsonObject, MC_Left_Elbow);
    JsonObjectBody->SetObjectField("LEFT_ELBOW", JsonObject);
    JsonObject = MakeShareable(new FJsonObject);

    // LEFT_HAND
    getLocationRotationOfComponent(JsonObject, MC_Left_Hand);
    JsonObjectBody->SetObjectField("LEFT_HAND", JsonObject);
    JsonObject = MakeShareable(new FJsonObject);

    FString OutputString;

    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(JsonObjectBody.ToSharedRef(), Writer);

    UE_LOG(LogTemp, Warning, TEXT("resulting jsonString -> %s"), *OutputString);

    return OutputString;

}


// Called every frame
void AIKPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FString ContentJsonString = createJson();
    
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpService->PostRequest("/raw_data", ContentJsonString);
    HttpService->Send(Request);

    //http post json 
    /*if (GEngine) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
            FString::Printf(TEXT("MC_Left_Hand: %s;"),
                *MC_Left_Hand->GetComponentLocation().ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
            FString::Printf(TEXT("MC_Left_Elbow: %s;"),
                *MC_Left_Elbow->GetComponentLocation().ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
            FString::Printf(TEXT("MC_Left_Shoulder: %s;"),
                *MC_Left_Shoulder->GetComponentLocation().ToString()));
    }*/
}

// Called to bind functionality to input
void AIKPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AIKPawn::parseJoints(TSharedPtr<FJsonObject> JsonObject, TSharedRef<TJsonReader<TCHAR>> Reader) {
   
    // распарсить по каждому датчику

    TSharedPtr<FJsonObject> Response = JsonObject->GetObjectField("LEFT_ELBOW");

    TArray<TSharedPtr<FJsonValue>> arr = Response->GetArrayField("L");

    for (auto& obj : arr)
    {
        auto value = obj->AsNumber();

        UE_LOG(LogTemp, Warning, TEXT("Value = %f"), value);

    }

}

void AIKPawn::OnBotResponseReceived(FString ResponseString) {
    
    TSharedPtr<FJsonObject> JsonObject;
    
    TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(ResponseString);
    
    UE_LOG(LogTemp, Warning, TEXT("Try parse %s"), *ResponseString);

    if (!FJsonSerializer::Deserialize(Reader, JsonObject)) {
        UE_LOG(LogTemp, Warning, TEXT("Cant deserialize response!"));
        return;
    }

    parseJoints(JsonObject, Reader);

}