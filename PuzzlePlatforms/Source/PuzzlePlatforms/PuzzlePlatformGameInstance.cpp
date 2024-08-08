// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"

#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "PlatformTrigger.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));

	if (MenuBPClass.Class != NULL)
	{
		MenuClass = MenuBPClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Class Not found: '/Game/MenuSystem/WBP_MainMenu'"));
	}

}

void UPuzzlePlatformGameInstance::Init()
{
	if (MenuClass.GetDefaultObject() != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Menu class: %s"), *MenuClass.Get()->GetName());
	}
}

void UPuzzlePlatformGameInstance::LoadMenu()
{
	if (MenuClass.GetDefaultObject() == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("No Menu class found!"));
		return;
	}
	
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	
	if(ensure(Menu != nullptr))
	{
		Menu->SetMenuInterface(this);
		Menu->Setup();
	}
	
}

void UPuzzlePlatformGameInstance::Host()
{
	if (Menu)
	{
		Menu->TearDown();
	}

	UEngine* Eng = GetEngine();
	if (!ensure(Eng != nullptr)) return;

	Eng->AddOnScreenDebugMessage(0, 4.0f, FColor::Green, TEXT("Hosting..."));

	GetWorld()->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void UPuzzlePlatformGameInstance::Join(const FString& Address)
{
	if (Menu)
	{
		Menu->TearDown();
	}

	UEngine* Eng = GetEngine();
	if (!ensure(Eng != nullptr)) return;

	Eng->AddOnScreenDebugMessage(0, 4.0f, FColor::Green, FString::Printf(TEXT("Joining: %s"), *Address));

	APlayerController* PController = GetFirstLocalPlayerController();
	PController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
