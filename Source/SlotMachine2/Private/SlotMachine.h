// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlotMachine.generated.h" 

UCLASS()
class ASlotMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlotMachine();

	UFUNCTION()
    void Spin(UStaticMeshComponent* Wheel, int32 ReelIndex);

	//UFUNCTION()
	//void SpinWheels();

	UFUNCTION()
	void StopWheelSpin();  

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 
	
	FRotator InitialRotation;
	FRotator TargetRotation;
	float LerpAlpha;   
	bool bIsRotating;
	bool bIsReturning;
	 
	//wheel
	bool bIsWheelRotating;
	FTimerHandle SpinTimerHandle; 

	int32 WheelPositions[3]; 
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* WheelGroup;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* LeverGroup;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* LeverRotateGroup;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WheelComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Wheel1Comp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Wheel2Comp;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LeverComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SphereComp;
	
	UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MachineComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LightComp;

	UPROPERTY(EditAnywhere)
	UMaterial* LightMaterial;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* FeuxArtifice;
};
