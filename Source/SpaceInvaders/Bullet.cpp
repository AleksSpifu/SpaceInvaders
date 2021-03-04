// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	Movement.X = MovementSpeed;
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerMovement.X < 50.f) {
		PlayerMovement.X = 50.f;
	}
	
	AddActorLocalOffset(((Movement - (Movement / 2 * !bIsFromPlayer)) + (PlayerMovement * bIsFromPlayer)) * DeltaTime);

	if (TimeAlive > TimeToDie) {
		Destroy();
	}
	else {
		TimeAlive += DeltaTime;
	}
}



