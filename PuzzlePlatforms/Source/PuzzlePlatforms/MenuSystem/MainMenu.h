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

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void ConfirmJoin();

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* BTN_Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* BTN_Join;

	UPROPERTY(meta = (BindWidget))
	class UButton* BTN_JoinCancel;

	UPROPERTY(meta = (BindWidget))
	class UButton* BTN_JoinConfirm;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* TXTB_IPAddress;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;


	IMenuInterface* MenuInterface;
	
};
