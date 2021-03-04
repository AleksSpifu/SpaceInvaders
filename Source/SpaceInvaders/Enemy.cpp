// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
	CoolDownBetweenShots = FMath::RandRange(2.f, 7.f);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer += DeltaTime;

	if (!GameManager->GameOver) {
		int Direction = (int)Timer % 4;

		AddActorLocalOffset(MoveDirections[Direction] * DeltaTime * MoveSpeed);

		if (GetActorLocation().X < -3775) {

			GameManager->GameOver = true;
		}

		if (Timer > CoolDownBetweenShots) {
			Shoot();
			CoolDownBetweenShots += FMath::RandRange((float)GameManager->NumberOfWaves, (float)GameManager->NumberOfWaves + 3.f);
			CoolDownBetweenShots -= GameManager->CurrentWave;
		}

	}
}



void AEnemy::Shoot()
{
	if (!GameManager->GameOver) {
		if (Bullet) {
			FRotator Rotation = GetActorRotation();
			Rotation.Yaw += 180.f;
			ABullet* BulletSpawned = GetWorld()->SpawnActor<ABullet>(Bullet, GetActorLocation() + SpawnOffset, Rotation);
			UE_LOG(LogTemp, Warning, TEXT("Bang!"));
			if (BulletSpawned) {
				BulletSpawned->bIsFromPlayer = false;
			}
		}
	}
}

void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ABullet::StaticClass())) {
		ABullet* bullet = Cast<ABullet>(OtherActor);
		OtherActor->Destroy();
		if (bullet->bIsFromPlayer && bullet->TimeAlive > .1f) {
			UE_LOG(LogTemp, Warning, TEXT("I'm Hit!"));
			GameManager->NumberOfEnemiesAlive--;
			UE_LOG(LogTemp, Warning, TEXT("Enemies left: %d"), GameManager->NumberOfEnemiesAlive);
			Destroy();

		}
	}
	else if (OtherActor->IsA(APlayerPawn::StaticClass())) {
		GameManager->GameOver = true;
	}
}

