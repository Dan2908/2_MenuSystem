// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "MenuSystem/MainMenu.h"

#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:

	UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	//~ Start IMenuInterface
	UFUNCTION(Exec)
	virtual void Host() override;
	UFUNCTION(Exec)
	virtual void Join(const FString& Address) override;
	//~ End IMenuInterface

	TSubclassOf<class UUserWidget> MenuClass;

	class UMainMenu* Menu;
};
