// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "MenuInterface.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/WidgetSwitcher.h"
#include "PuzzlePlatforms/PuzzlePlatformGameInstance.h"


bool UMainMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	BTN_Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	BTN_Join->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	BTN_JoinCancel->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	BTN_JoinConfirm->OnClicked.AddDynamic(this, &UMainMenu::ConfirmJoin);

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

void UMainMenu::OpenJoinMenu()
{
	if (ensure(MenuSwitcher) && ensure(JoinMenu))
	{
		MenuSwitcher->SetActiveWidget(JoinMenu);
	}
}

void UMainMenu::OpenMainMenu()
{
	if (ensure(MenuSwitcher) && ensure(MainMenu))
	{
		MenuSwitcher->SetActiveWidget(MainMenu);
	}
}

void UMainMenu::ConfirmJoin()
{
	if (MenuInterface)
	{
		MenuInterface->Join(TXTB_IPAddress->GetText().ToString());
	}
}
