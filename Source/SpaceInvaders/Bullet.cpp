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

	//Kopierer MovementSpeed som kan redigeres i editoren, og legger den til vektoren som flytter kula.
	Movement.X = MovementSpeed;
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Siden kula f�r farten til spilleren n�r den blir skutt, hendte det av og til at kula bare stod stille n�r dem ble skutt.
	// Derfor gj�r jeg s�nn at den ihvertfall beveger seg litt, selv om det strider litt i mot den realistiske fysikken jeg gikk for.
	if (PlayerMovement.X < 50.f) {
		PlayerMovement.X = 50.f;
	}
	
	// Den her ser helt j�vlig ut, men den gj�r 2 ting:

	// 1. ((Movement - (Movement / 2 * !bIsFromPlayer))
	// Legger f�rst p� Movement vektoren, ogs� trekker jeg fra halvparten av movement hvis den kommer fra en fiende. 
	// P� denne m�ten g�r kulene litt saktere hvis de er skutt fra fiendene. 

	// 2. pluss p� PlayerMovement vektoren som kommer n�r spilleren spawner kula, men bare hvis kula kommer fra spilleren.

	AddActorLocalOffset(((Movement - (Movement / 2 * !bIsFromPlayer)) + (PlayerMovement * bIsFromPlayer)) * DeltaTime);

	//Her blir den fjernet hvis det har g�tt for lang tid. 
	if (TimeAlive > TimeToDie) {
		Destroy();
	}
	else {
		TimeAlive += DeltaTime;
	}
}



