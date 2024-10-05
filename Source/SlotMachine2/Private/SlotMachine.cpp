// Fill out your copyright notice in the Description page of Project Settings.

#include "SlotMachine.h" 
#include "NiagaraComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

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
            Spin(WheelComp);
            Spin(Wheel1Comp);
            Spin(Wheel2Comp); 
        }
}

//Fonction pour faire tourner mes wheels
void ASlotMachine::Spin(UStaticMeshComponent* Wheel)
{
    if (Wheel)
    { 
        int32 RandomInt = FMath::RandRange(0, 15); 
        float NewRotationPitch = RandomInt * 22.5f; 
    
        Wheel->SetRelativeRotation(FRotator(0.f, NewRotationPitch, 0.f));
    }
} 
 