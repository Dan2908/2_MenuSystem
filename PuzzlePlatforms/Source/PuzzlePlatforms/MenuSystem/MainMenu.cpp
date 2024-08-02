// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "PuzzlePlatforms/PuzzlePlatformGameInstance.h"


bool UMainMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	BTN_Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* Interface)
{
	this->MenuInterface = Interface;
}

void UMainMenu::Setup()
{
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PController = World->GetFirstPlayerController())
		{
			// input mode
			FInputModeUIOnly InputModeData;
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputModeData.SetWidgetToFocus(this->TakeWidget());

			PController->SetInputMode(InputModeData);
			PController->SetShowMouseCursor(true);
		}

		this->AddToViewport();
	}

}

void UMainMenu::TearDown()
{
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PController = World->GetFirstPlayerController())
		{
			// input mode
			FInputModeGameOnly InputModeData;
			InputModeData.SetConsumeCaptureMouseDown(false);

			PController->SetInputMode(InputModeData);
			PController->SetShowMouseCursor(false);
		}

		NativeDestruct();
	}
}

void UMainMenu::HostServer()
{
	if (MenuInterface)
	{
		MenuInterface->Host();
	}
}
