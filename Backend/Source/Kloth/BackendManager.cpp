// Fill out your copyright notice in the Description page of Project Settings.


#include "BackendManager.h"

// Sets default values
ABackendManager::ABackendManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABackendManager::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ABackendManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!busy) {
		if (LoadJob()) {
			StartJob();
		}
		return;
	}
}

bool ABackendManager::LoadJob() {
	if (!FPaths::FileExists(body_parameters)) {
		UE_LOG(LogTemp, Fatal, TEXT("parameter file not found"));
		return false;
	}
	FString json;
	if (!FFileHelper::LoadFileToString(json, *body_parameters)) {
		UE_LOG(LogTemp, Fatal, TEXT("parameter file could not be loaded"));
		return false;
	}

	TSharedPtr<FJsonObject> rootObject;
	TSharedRef<TJsonReader<>> readerObject = TJsonReaderFactory<>::Create(json);

	if (!FJsonSerializer::Deserialize(readerObject, rootObject)) {
		UE_LOG(LogTemp, Fatal, TEXT("could not deserialize json")); 
		return false;
	}

	jobparams.waistSize = FCString::Atof(*(rootObject->GetStringField(TEXT("waist"))));
	jobparams.cloth = rootObject->GetStringField(TEXT("cloth"));
	jobparams.cloth_size = rootObject->GetStringField(TEXT("cloth_size"));
	return true;
}

void ABackendManager::StartJob() {
	const FString BP_path = TEXT("/Game/MetaHumans/MH_Body/BP_MH_Body.BP_MH_Body_C");
	UClass* MHClass = LoadObject<UClass>(nullptr, *BP_path);
	if (!MHClass) {
		UE_LOG(LogTemp, Error, TEXT("could not load metahuman bp"));
		return;
	}
	if (!MetaHumanActor) {
		MetaHumanActor = GetWorld()->SpawnActor<AActor>(MHClass);
		if (!MetaHumanActor) {
			UE_LOG(LogTemp, Error, TEXT("failed to spawn metahuman"));
			return;
		}
	}

	//if (!OutfitComponent) {
	//	TArray<USkeletalMeshComponent*> SkelComps;
	//	MetaHumanActor->GetComponents<USkeletalMeshComponent>(SkelComps);
	//	FString desiredMesh = "WI_"+jobparams.cloth + jobparams.cloth_size;
	//	/*for (auto* comp : SkelComps) {
	//		FString meshName = comp->GetSkeletalMeshAsset()->GetName();
	//		UE_LOG(LogTemp, Error, TEXT(" Desired Meshname %s"), *desiredMesh);
	//		UE_LOG(LogTemp, Error, TEXT(" Current Meshname %s"), *meshName);
	//		if(meshName==desiredMesh)
	//			UE_LOG(LogTemp, Error, TEXT("MeshFound"));
	//	}*/
	//}
	
}