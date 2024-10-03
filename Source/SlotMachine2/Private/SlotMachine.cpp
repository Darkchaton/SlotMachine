// Fill out your copyright notice in the Description page of Project Settings.

#include "NiagaraComponent.h"
#include "SlotMachine.h"

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
	WheelGroup->SetupAttachment(SceneRoot);

	WheelComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComp"));
	WheelComp->SetupAttachment(WheelGroup);

	Wheel1Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel1Comp"));
	Wheel1Comp->SetupAttachment(WheelGroup);

	Wheel2Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel2Comp"));
	Wheel2Comp->SetupAttachment(WheelGroup);

	LeverGroup = CreateDefaultSubobject<USceneComponent>(TEXT("LeverGroup"));
	LeverGroup->SetupAttachment(SceneRoot);

	LeverComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeverComp"));
	LeverComp->SetupAttachment(LeverGroup);

	SphereComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(LeverGroup);
	
	MachineComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MachineComp"));
    MachineComp->SetupAttachment(LeverGroup);

	FeuxArtifice =  CreateDefaultSubobject<UNiagaraComponent>(TEXT("FeuxArtifice"));
	FeuxArtifice->SetupAttachment(CubeComp);

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

