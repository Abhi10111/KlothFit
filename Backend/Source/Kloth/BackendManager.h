// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "MetaHumanCharacter.h"
#include "BackendManager.generated.h"

USTRUCT()
struct FKlothJob {
	GENERATED_BODY()
	FString cloth;
	FString cloth_size;
	float waistSize;
};
UCLASS()
class KLOTH_API ABackendManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABackendManager();

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UMetaHumanWardrobeItem> OutfitComponent;*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool busy = false;

	FString root = TEXT("C:/Users/abhis/Desktop/KlothFit");
	FString body_parameters = TEXT("C:/Users/abhis/Desktop/KlothFit/Frontend/body_parameters.json");
	
	FKlothJob jobparams;

	UPROPERTY()
	AActor* MetaHumanActor = nullptr;

	bool LoadJob();
	void StartJob();

};
