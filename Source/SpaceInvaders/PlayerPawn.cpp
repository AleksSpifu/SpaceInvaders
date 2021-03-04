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
	GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentDirection.X != 0 || CurrentDirection.Y != 0) {
		AddActorLocalOffset(CurrentDirection * DeltaTime, true);
		if (TutorialStage == 1) {
			TutorialStage++;
		}
	}
	
	

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
	if (TutorialStage == 2) {
		TutorialStage++;
	}
	else if (TutorialStage == 6 && (CurrentDirection.X != 0 || CurrentDirection.Y != 0)) {
		TutorialStage++;
	}
	else if (TutorialStage == 7) {
		TutorialStage++;
	}
	if (!GameManager->GameOver) {
		if (Bullet && !ShotTaken) {
			ShotTaken = true;

			if (bGodMode) {
				if (TutorialStage == 4) {
					TutorialStage++;
				}
				FRotator Rotation = GetActorRotation();

				for (int i = -90; i <= 90; i += 20) {
					Rotation.Yaw = i;
					ABullet* BulletSpawned = GetWorld()->SpawnActor<ABullet>(Bullet, GetActorLocation() + SpawnOffset, Rotation);

					if (BulletSpawned) {
						BulletSpawned->PlayerMovement = CurrentDirection;
					}
				}

			}
			else {
				ABullet* BulletSpawned = GetWorld()->SpawnActor<ABullet>(Bullet, GetActorLocation() + SpawnOffset, GetActorRotation());

				if (BulletSpawned) {
					BulletSpawned->PlayerMovement = CurrentDirection;
				}
			}
		}
	}
}

