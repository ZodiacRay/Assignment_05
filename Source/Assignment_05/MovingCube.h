// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingCube.generated.h"



UCLASS()
class ASSIGNMENT_05_API AMovingCube : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	FTimerHandle MoveTimer; 

protected:

	// 이동 횟수 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Count")
	int32 MovementCount = 0; 

	// 이벤트 발동 횟수 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Count")
	int32 EventCount = 0;

	// 쿨타임 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float MoveCoolDown = 2.f; 

	// 이동 범위 제한  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FVector MoveRange_Min = FVector(50.f, 50.f, 50.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FVector MoveRange_Max = FVector(500.f, 500.f, 500.f);
	
	FVector LastLocation; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MovementInfo")
	float TotalDistance = 0; 
	
	// 정지 ? 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stop")
	bool bShouldStop = false; 


protected:

	// Material 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterialInstance* CubeMaterial; 

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterialInst;

public:	
	// Sets default values for this actor's properties
	AMovingCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*턴 or 이동 (50%) */
	void DoTurnOrMove(); 

	/* 턴 */
	void Turn();

	/* 이동 */
	void Move(); 

	/* 이동 정보 (현재 위치, 이동 횟수) 출력 */
	void PrintMoveInfo(); 

	/* 이동 횟수 증가 */
	void IncreaseMovementCount(); 

	/* 이벤트 - 크기 변화 */
	void SetRandomScale(); 

	void SetMaterialRandomColor(); 

	/*이벤트 정보 (현재 스케일, 이벤트 발동 횟수) 출력 */
	void PrintScaleInfo();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




};
