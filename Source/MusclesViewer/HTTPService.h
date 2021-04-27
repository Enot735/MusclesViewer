// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "Engine.h"
#include "HTTPService.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MUSCLESVIEWER_API AHTTPService : public AActor
{
	GENERATED_BODY()
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResponseReceivedDelegate, FString, ResponseString);
public:	
	// Sets default values for this actor's properties
	AHTTPService();

    void ResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

    UPROPERTY(BlueprintAssignable, BlueprintCallable)
    FResponseReceivedDelegate OnResponseReceived;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    FHttpModule *Http;
    FString APIBaseUrl;
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> RequestWithRoute(FString Subroute);
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> GetRequest(FString Subroute);
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> PostRequest(FString Subroute, FString ContentJsonString);

    void Send(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request);
    bool ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
