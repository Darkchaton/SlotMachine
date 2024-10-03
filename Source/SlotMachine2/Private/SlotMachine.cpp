// Fill out your copyright notice in the Description page of Project Settings.

#include "SlotMachine.h"
#include "NiagaraComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ASlotMachine::ASlotMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	CubeComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeComp"));
	CubeComp->SetupAttachment(SceneRoot);

	WheelGroup = CreateDefaultSubobject<USceneComponent>(TEXT("WheelGroup"));
	WheelGroup->SetupAttachment(RootComponent);

	WheelComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComp"));
	WheelComp->SetupAttachment(WheelGroup);

	Wheel1Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel1Comp"));
	Wheel1Comp->SetupAttachment(WheelGroup);

	Wheel2Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel2Comp"));
	Wheel2Comp->SetupAttachment(WheelGroup);
 
	LeverRotateGroup = CreateDefaultSubobject<USceneComponent>(TEXT("LeverRotateGroup"));
	LeverRotateGroup->SetupAttachment(RootComponent);

	LeverGroup = CreateDefaultSubobject<USceneComponent>(TEXT("LeverGroup"));
	LeverGroup->SetupAttachment(LeverRotateGroup);

	LeverComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeverComp"));
	LeverComp->SetupAttachment(LeverGroup);

	SphereComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(LeverGroup);
	
	MachineComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MachineComp"));
    MachineComp->SetupAttachment(LeverRotateGroup);

	FeuxArtifice =  CreateDefaultSubobject<UNiagaraComponent>(TEXT("FeuxArtifice"));
	FeuxArtifice->SetupAttachment(CubeComp);

}

void ASlotMachine::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	UE_LOG(LogTemp, Warning, TEXT("Collision connectée"));
}

// Called when the game starts or when spawned
void ASlotMachine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlotMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
}

