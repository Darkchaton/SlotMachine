// Fill out your copyright notice in the Description page of Project Settings.

#include "SlotMachine.h" 
#include "NiagaraComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
ASlotMachine::ASlotMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Variables
	InitialRotation = FRotator::ZeroRotator; 
	LerpAlpha = 0.f;
	bIsRotating = false;
	bIsReturning = false; 
	bIsWheelRotating= false;

	FMemory::Memset(WheelPositions, -1, sizeof(WheelPositions));
	
	//Slot machine
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	CubeComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeComp"));
	CubeComp->SetupAttachment(SceneRoot);

	WheelGroup = CreateDefaultSubobject<USceneComponent>(TEXT("WheelGroup"));
	WheelGroup->SetupAttachment(RootComponent);

	WheelComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelComp"));
	WheelComp->SetupAttachment(SceneRoot);

	Wheel1Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel1Comp"));
	Wheel1Comp->SetupAttachment(SceneRoot);

	Wheel2Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel2Comp"));
	Wheel2Comp->SetupAttachment(SceneRoot);
 
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

	//Lumières

	LightComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightComp"));
	LightComp->SetupAttachment(SceneRoot);

	//Particules
	FeuxArtifice =  CreateDefaultSubobject<UNiagaraComponent>(TEXT("FeuxArtifice"));
	FeuxArtifice->SetupAttachment(CubeComp); 
}

//NOTIFY HIT
void ASlotMachine::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	TargetRotation = FRotator(0.f, 0.f, 45.f);
	LerpAlpha = 0.f; 
	bIsRotating = true;
	bIsReturning = false; 
	bIsWheelRotating = true;
}

// Called when the game starts or when spawned
void ASlotMachine::BeginPlay()
{
	Super::BeginPlay();
	InitialRotation = LeverGroup->GetRelativeRotation();
}

// Called every frame
void ASlotMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
	
	//Levier
	if (bIsRotating)
	{ 
		LerpAlpha += DeltaTime;   
		if (LerpAlpha >= 1.0f)
		{
			LerpAlpha = 1.0f;   
			bIsRotating = false;
			bIsReturning = true;
		}
 
		FRotator NewRotation = FMath::Lerp(InitialRotation, TargetRotation, LerpAlpha);
		LeverGroup->SetRelativeRotation(NewRotation);
	}
	else if (bIsReturning) 
	{
		LerpAlpha += DeltaTime;
		if (LerpAlpha >= 1.0f)
		{
			LerpAlpha = 1.0f;
			bIsReturning = false;  
		}

		FRotator NewRotation = FMath::Lerp(TargetRotation, InitialRotation, LerpAlpha);
		LeverGroup->SetRelativeRotation(NewRotation);
	}
	
	//Wheels
	 if (bIsWheelRotating)
     {  
	 	Spin(WheelComp, 0);   
	 	Spin(Wheel1Comp, 1);  
	 	Spin(Wheel2Comp, 2);
     }
}

//Fonction pour faire tourner mes wheels
void ASlotMachine::Spin(UStaticMeshComponent* Wheel, int32 ReelIndex)
{
    if (Wheel)
    {
    	WheelPositions[ReelIndex] = FMath::RandRange(0, 15);
    	float NewRotationPitch = WheelPositions[ReelIndex] * 22.5f;
    	  
    	Wheel->AddLocalRotation(FRotator(0.f, NewRotationPitch, 0.f));
    	 
    	if (!GetWorld()->GetTimerManager().IsTimerActive(SpinTimerHandle))
    	{
    		GetWorld()->GetTimerManager().SetTimer(SpinTimerHandle, this, &ASlotMachine::StopWheelSpin, 3.0f, false); 
    	}  
    } 
}

void ASlotMachine::StopWheelSpin()
{
	bIsWheelRotating = false; 
	UE_LOG(LogTemp, Warning, TEXT("Final Position for Wheel 0: %d"), WheelPositions[0]);
	UE_LOG(LogTemp, Warning, TEXT("Final Position for Wheel 1: %d"), WheelPositions[1]);
	UE_LOG(LogTemp, Warning, TEXT("Final Position for Wheel 2: %d"), WheelPositions[2]);

	//(Ma wheel 0 est au début, ma wheel 2 est au milieu et ma wheel 1 est à la fin, désolée) pour le debug: 
	if (WheelPositions[0] == WheelPositions[1]) // Compare la première et la deuxième roue 
	//if (WheelPositions[0] == WheelPositions[1] && WheelPositions[0] == WheelPositions[2])  
	{
		UE_LOG(LogTemp, Warning, TEXT("WIN"));
			 
		FeuxArtifice->SetVariableFloat(TEXT("FeuxArtifice"), 100);
		LightComp->SetMaterial(0, LightMaterial);
	} 
	else{
			UE_LOG(LogTemp, Warning, TEXT("LOSE"));
	}  
	GetWorld()->GetTimerManager().ClearTimer(SpinTimerHandle);  
}