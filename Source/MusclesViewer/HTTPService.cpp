// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPService.h"

// Sets default values
AHTTPService::AHTTPService()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    APIBaseUrl = TEXT("http://localhost:50691/gameservice.svc");
}

// Called when the game starts or when spawned
void AHTTPService::BeginPlay()
{
	Super::BeginPlay();
    Http = &FHttpModule::Get();
    UE_LOG(LogTemp, Warning, TEXT("HttpServer started: %s"), *APIBaseUrl);
}
	

// Called every frame
void AHTTPService::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> AHTTPService::RequestWithRoute(FString Subroute) {
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
    Request->SetURL(APIBaseUrl + Subroute);
    Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
    return Request;
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> AHTTPService::GetRequest(FString Subroute) {
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = RequestWithRoute(Subroute);
    Request->OnProcessRequestComplete().BindUObject(this, &AHTTPService::ResponseReceived);
    Request->SetVerb("GET");
    return Request;
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> AHTTPService::PostRequest(FString Subroute, FString ContentJsonString) {
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = RequestWithRoute(Subroute);
    Request->SetVerb("POST");
    Request->SetContentAsString(ContentJsonString);
    return Request;
}

void AHTTPService::Send(TSharedRef<IHttpRequest, ESPMode::ThreadSafe> &Request) {
    Request->ProcessRequest();
}
 
bool AHTTPService::ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful) {
    if ((!bWasSuccessful) || (!Response.IsValid())) {
        return false;
    }
    if (EHttpResponseCodes::IsOk(Response->GetResponseCode())) {
        return true;
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Http Response returned error code: %d"), Response->GetResponseCode());
        return false;
    }
}

void AHTTPService::ResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
    UE_LOG(LogTemp, Warning, TEXT("Get Answer %s"), *Response->GetContentAsString());
    FString ResponseString = Response->GetContentAsString().Replace(TEXT("\\n"), TEXT(" "));
    OnResponseReceived.Broadcast(ResponseString);
}

