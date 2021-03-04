// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	// Skaffer en referanse til sjefen her og
	GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// CurrentDirection blir oppdatert i de bevegelsesfunksjonene, s� blir den matet inn her. Hvis tutorial stage er p� 1 
	// (Der det st�r "bruk WASD") s� har spilleren bevegd p� seg, og vi kan vise neste beskjed.

	if (CurrentDirection.X != 0 || CurrentDirection.Y != 0) {
		AddActorLocalOffset(CurrentDirection * DeltaTime, true);
		if (TutorialStage == 1) {
			TutorialStage++;
		}
	}
	
	
	// S�rg for at man ikke kan skyte altfor mange skudd fort. Denne kan stilles inn i editoren.
	if (ShotTaken) {

		if (LastShotTaken < CooldownBetweenShots) {
			LastShotTaken += DeltaTime;
		}
		else {
			LastShotTaken = 0.f;
			ShotTaken = false;
		}
	}
}

void APlayerPawn::ToggleGodMode()
{
	// God mode her er ikke slik man kanskje vil tolke god mode med en gang. Man blir ikke ud�delig, men man skyter en hel haug med kuler istedenfor 1.
	// Dette var for � gj�re det raskere � teste n�r man ble ferdig med spillet for eksempel. 
	// Det er ogs� noen steg i tutorial som er relevant her, s� hvis spilleren trykker riktig, g� til neste punkt.
	bGodMode = !bGodMode;
	if (TutorialStage == 3) {
		TutorialStage++;
	}
	else if (TutorialStage == 5) {
		TutorialStage++;
	}
}

void APlayerPawn::Restart()
{
	// S�nn at man skal kunne trykke p� en knapp for � restarte m�tte jeg gj�re s�nn her, jeg satte GameManager som en Actor f�r jeg tenkte p� det, 
	// S� det ble litt tr�lete � legge inn input component og hele greia der.
	if (GameManager && GameManager->Timer > 1.f) {
		GameManager->Restart();

	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Up", this, &APlayerPawn::MoveUp);
	PlayerInputComponent->BindAxis("Right", this, &APlayerPawn::MoveRight);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerPawn::Shoot);
	PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &APlayerPawn::Restart);
	PlayerInputComponent->BindAction("GodMode", IE_Pressed, this, &APlayerPawn::ToggleGodMode);

}

void APlayerPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Hvis spilleren blir skutt av en fiende, game over.
	if (OtherActor->IsA(ABullet::StaticClass())) {
		ABullet* bullet = Cast<ABullet>(OtherActor);
		if (!bullet->bIsFromPlayer) {
			UE_LOG(LogTemp, Warning, TEXT("Player has been Hit!"));
			OtherActor->Destroy();
			GameManager->GameOver = true;
		}
	}
}

void APlayerPawn::MoveRight(float speed)
{
	// S�rger for at spilleren ikke kan g� utafor bana, og heller ikke n�r det er game over. Samme opplegg i MoveUp
	if (!GameManager->GameOver) {
		FVector Location = GetActorLocation();
		if (Location.Y > 1700) {
			CurrentDirection.Y = FMath::Clamp(speed, -1.f, 0.f) * MoveSpeed;
		}
		else if (Location.Y < -1700) {
			CurrentDirection.Y = FMath::Clamp(speed, 0.f, 1.f) * MoveSpeed;
		}
		else {
			CurrentDirection.Y = FMath::Clamp(speed, -1.f, 1.f) * MoveSpeed;
		}
	}
	else {
		CurrentDirection.Y = 0.f;
	}
	
}

void APlayerPawn::MoveUp(float speed)
{
	
	if (!GameManager->GameOver) {
		FVector Location = GetActorLocation();
		if (Location.X < -3770) {
			CurrentDirection.X = FMath::Clamp(speed, 0.f, 1.f) * MoveSpeed;
		}
		else if (Location.X > -830) {
			CurrentDirection.X = FMath::Clamp(speed, -1.f, 0.f) * MoveSpeed;
		}
		else {
			CurrentDirection.X = FMath::Clamp(speed, -1.f, 1.f) * MoveSpeed;
		}
	}
	else {
		CurrentDirection.X = 0.f;
	}
}

void APlayerPawn::Shoot()
{
	// Her ogs� er det noen tutorials som er relevante.
	if (TutorialStage == 2) {
		TutorialStage++;
	}
	else if (TutorialStage == 6 && (CurrentDirection.X != 0 || CurrentDirection.Y != 0)) {
		TutorialStage++;
	}
	else if (TutorialStage == 7) {
		TutorialStage++;
	}

	// Denne er ganske enkel den og, det som ser verst ut er egentlig n�r GodMode er p�, men den og er ikke s� f�l.

	if (!GameManager->GameOver) {
		if (Bullet && !ShotTaken) {
			ShotTaken = true;

			if (bGodMode) {
				if (TutorialStage == 4) {
					TutorialStage++;
				}
				FRotator Rotation = GetActorRotation();

				// Lagrer rotasjonen, ogs� starter p� -90 og g�r til +90 med 20 graders intervall, og spawner en kule den retningen. 
				for (int i = -90; i <= 90; i += 20) {
					Rotation.Yaw = i;
					ABullet* BulletSpawned = GetWorld()->SpawnActor<ABullet>(Bullet, GetActorLocation() + SpawnOffset, Rotation);

					// Legger inn spillerens fart til kula slik at den beveger seg litt i retningen man beveger seg n�r man skyter.
					// Syns dette var en kul m�te � skyte selv om det er farlig � st� rett i skuddlinja til fiendene, og det �pner opp
					// for mulighet om at man kan ha hindringer for eksempel, slik at man M� skyte skr�tt. Eller at kulene spretter p� vegger kanskje,
					// s� kan man finne p� mye kule m�ter � spille p�. Jeg har jo ikke gjort noe av det, men muligheten er der ihvertfall.
					if (BulletSpawned) {
						BulletSpawned->PlayerMovement = CurrentDirection;
					}
				}

			}

			// Dette er den vanlige kula, samme opplegg med at farten til spilleren er med i bildet, men kun 1 kule til vanlig.
			else {
				ABullet* BulletSpawned = GetWorld()->SpawnActor<ABullet>(Bullet, GetActorLocation() + SpawnOffset, GetActorRotation());

				if (BulletSpawned) {
					BulletSpawned->PlayerMovement = CurrentDirection;
				}
			}
		}
	}
}

