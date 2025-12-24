// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingCube.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"


// Sets default values
AMovingCube::AMovingCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube")); 
	RootComponent = StaticMesh; 
	
}

// Called when the game starts or when spawned
void AMovingCube::BeginPlay()
{
	Super::BeginPlay();
	

	if (CubeMaterial)
	{
		// 다이나믹 머터리얼 인스턴스 생성 
		DynamicMaterialInst = StaticMesh->CreateDynamicMaterialInstance(0, CubeMaterial, TEXT("None"));
	}
	
	// 시작점은 (0, 50, 0)이고 한번 이동시 현재 좌표 및 이동 횟수를 출력 합니다.
	SetActorLocation(FVector(0, 50, 0)); 

	// 타이머 설정 
	GetWorld()->GetTimerManager().SetTimer(
		MoveTimer, 
		this,
		&ThisClass::DoTurnOrMove,
		MoveCoolDown,
		false
	); 
}

void AMovingCube::DoTurnOrMove()
{
	// 랜덤 확률 (50%) 
	int32 RandValue = FMath::RandRange(1, 2);

	if (RandValue == 1)
		Turn(); // 회전 
	else
		Move(); // 이동 
	
	if (!bShouldStop)
	{
		// 다시 타이머 리셋 
		GetWorld()->GetTimerManager().SetTimer(
			MoveTimer,
			this,
			&ThisClass::DoTurnOrMove,
			MoveCoolDown,
			false
		);
	}
}

void AMovingCube::Move()
{
	// 이동 
	LastLocation = GetActorLocation(); 

	const FVector NewLocation = FVector(
		FMath::FRandRange(MoveRange_Min.X, MoveRange_Max.X),
		FMath::FRandRange(MoveRange_Min.Y, MoveRange_Max.Y),
		FMath::FRandRange(MoveRange_Min.Z, MoveRange_Max.Z)
	);

	SetActorLocation(NewLocation);

	// 현재 좌표, 이동횟수 출력 
	PrintMoveInfo(); 

	// 이동 횟수 증가 
	IncreaseMovementCount(); 
}

void AMovingCube::PrintMoveInfo()
{
	// 현재 위치 
	const FVector Location = GetActorLocation();
	
	const FString LocationStr = FString::Printf(
		TEXT("Location: X=%.2f Y=%.2f Z=%.2f"),
		Location.X,
		Location.Y,
		Location.Z
	);

	// 이동 거리 
	const float Distance = FVector::Distance(Location, LastLocation);
	TotalDistance += Distance; 

	const FString DistanceStr = TEXT("Distance: ") + FString::SanitizeFloat(Distance);

	// 움직인 횟수 
	const FString MovementStr = TEXT("Movement: ") + FString::FromInt(MovementCount);

	

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, LocationStr);
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, MovementStr);
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, DistanceStr);
	}
}

void AMovingCube::IncreaseMovementCount()
{
	MovementCount++;
	if (MovementCount % 10 == 0)
	{
		// 랜덤 (50%) 
		const int32 RandValue = FMath::RandRange(1, 2); 
		if (RandValue == 1)
		{
			EventCount++; 
			SetRandomScale();

			SetMaterialRandomColor(); 
		}
		
	}
}

void AMovingCube::SetRandomScale()
{
	const FVector NewScale = FVector(
		FMath::FRandRange(0, 5.f),
		FMath::FRandRange(0, 5.f),
		FMath::FRandRange(0, 5.f)
	);

	// 크기 변화 이벤트 
	SetActorScale3D(NewScale);
	
	// 현재 스케일, 이벤트 횟수 출력
	PrintScaleInfo();
}

void AMovingCube::SetMaterialRandomColor()
{
	FLinearColor Color = FLinearColor::MakeRandomColor();
	
	if (DynamicMaterialInst)
	{
		DynamicMaterialInst->SetVectorParameterValue(FName("Color"), Color);
	}
}

void AMovingCube::PrintScaleInfo()
{
	const FVector Scale = GetActorScale3D(); 

	const FString ScaleStr = FString::Printf(
		TEXT("NewScale: X=%.2f Y=%.2f Z=%.2f"),
		Scale.X,
		Scale.Y,
		Scale.Z
	);
	const FString MovementStr = TEXT("EventCount: ") + FString::FromInt(EventCount);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, ScaleStr);
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, MovementStr);
	}
	
}

void AMovingCube::Turn()
{
	const FRotator NewRotation = FRotator(
		FMath::FRandRange(0.f, 360.f),
		FMath::FRandRange(0.f, 360.f),
		FMath::FRandRange(0.f, 360.f)
	);

	SetActorRotation(NewRotation);
}

// Called every frame
void AMovingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

