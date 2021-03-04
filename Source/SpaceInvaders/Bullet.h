// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SPACEINVADERS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// For å holde styr på om den kommer fra spilleren eller ikke. Dette er fordi fiendene ikke skal drepe hverandre, og
	// Spilleren skal ikke kunne drepe seg selv
	bool bIsFromPlayer{ true };

	// Resten her er ganske standard
	UPROPERTY(EditAnywhere)
		float MovementSpeed{ 1000.f };
	FVector Movement{ 0.f };
	FVector PlayerMovement{ 0.f };

	UPROPERTY(EditAnywhere)
		float TimeToDie{ 30.f };

	float TimeAlive{ 0.f };

	

};
