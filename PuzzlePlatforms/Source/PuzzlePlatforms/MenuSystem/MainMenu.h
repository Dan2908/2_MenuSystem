// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class IMenuInterface;
/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetMenuInterface(IMenuInterface* Interface);

	void Setup();

	void TearDown();

protected:

	virtual bool Initialize() override;

	UFUNCTION()
	void HostServer();

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* BTN_Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* BTN_Join;

	IMenuInterface* MenuInterface;
	
};
