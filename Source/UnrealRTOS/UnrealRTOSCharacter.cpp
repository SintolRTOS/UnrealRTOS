// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UnrealRTOSCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/GameUserSettings.h"
#include "EntityManager.h"
#include "Json.h"

//////////////////////////////////////////////////////////////////////////
// AUnrealRTOSCharacter

AUnrealRTOSCharacter::AUnrealRTOSCharacter():
	_ambassador(NULL)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AUnrealRTOSCharacter::BeginPlay()
{
	Super::BeginPlay();
	UGameUserSettings::GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
	_charactorBehaviorTree.setCharactor(this);
	_charactorBehaviorTree.initBehaviorTrees();
	_charactorBehaviorTree.startBehaviorNode(IDLE);
	const FString WriteSection = "RTOSConfig";
	//String
	//GConfig->SetString(
	//	*WriteSection,
	//	TEXT("FedExecutionName"),
	//	TEXT("UnrealRTOS"),
	//	GGameIni
	//	);
	//GConfig->SetString(
	//	*WriteSection,
	//	TEXT("FedName"),
	//	TEXT("MultiAI"),
	//	GGameIni
	//	);
	//GConfig->Flush(false, GGameIni);
	FString FedExecutionName;
	GConfig->GetString(
		TEXT("RTOSConfig"),
		TEXT("FedExecutionName"),
		FedExecutionName,
		GGameIni
		);
	FString FedName;
	GConfig->GetString(
		TEXT("RTOSConfig"),
		TEXT("FedName"),
		FedName,
		GGameIni
		);
	FString FedFile;
	GConfig->GetString(
		TEXT("RTOSConfig"),
		TEXT("FedFile"),
		FedFile,
		GGameIni
		);
	FString NodeAddress;
	GConfig->GetString(
		TEXT("RTOSConfig"),
		TEXT("NodeAddress"),
		NodeAddress,
		GGameIni
		);
	UWorld* const World = GetWorld();
	if (TempleCharactor != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			SintolRTI::EntityManager::GetInstance()->setWolrd(World);
		}
		SintolRTI::EntityManager::GetInstance()->SetTempleEntityCharactor(TempleCharactor);
		//SintolRTI::EntityManager::GetInstance()->createAActorWithTemple(GetActorLocation()+ FVector(50,0,0), GetActorRotation());
	}

	std::wstring _wfedExecutionName = FedExecutionName.GetCharArray().GetData();
	std::wstring _wfedName = FedName.GetCharArray().GetData();
	std::wstring _wfedFile = FedFile.GetCharArray().GetData();
	std::wstring _nodeAddress = NodeAddress.GetCharArray().GetData();

	_fedTypeName = TCHAR_TO_UTF8(*FedName);

	_ambassador = new SintolRTI::UnrealRTOSAmbassador();
	rti1516::AttributeHandleSet _attributionset;
	SintolRTI::SDKManager::GetInstance()->InitSDK(*_ambassador, 
		_wfedExecutionName,
		_wfedName,
		_wfedFile,
		_nodeAddress);
	try {
		_characterObjHandle = SintolRTI::SDKManager::GetInstance()->getObjectClassHandle(L"MultiEntity");
		_characterAttributeHandle = SintolRTI::SDKManager::GetInstance()->getAttributeHandle(_characterObjHandle, L"playerAttribution");
		_attributionset.insert(_characterAttributeHandle);
	}
	catch (const rti1516::Exception& e) {
		std::wcout << L"rti1516::Exception: \"" << e.what() << L"\"" << std::endl;
		return;
	}
	catch (...) {
		std::wcout << L"Unknown Exception!" << std::endl;
		return;
	}

	try {
		SintolRTI::SDKManager::GetInstance()->publishObjectClassAttributes(_characterObjHandle, _attributionset);
		SintolRTI::SDKManager::GetInstance()->subscribeObjectClassAttributes(_characterObjHandle, _attributionset);
		_charactorObjInstance = SintolRTI::SDKManager::GetInstance()->registerObjectInstance(_characterObjHandle);
	}
	catch (const rti1516::Exception& e) {
		std::wcout << L"rti1516::Exception: \"" << e.what() << L"\"" << std::endl;
		return;
	}
	catch (...) {
		std::wcout << L"Unknown Exception!" << std::endl;
		return;
	}
}

void AUnrealRTOSCharacter::Tick(float DeltaSeconds)
{
	_invervalTime += DeltaSeconds;
	FVector _charactorLocation = GetActorLocation();
	FString _locationstr = _charactorLocation.ToString();
	FRotator _charactorRotation = GetActorRotation();
	FString _rotationstr = _charactorRotation.ToString();
	FString _velocity = GetVelocity().ToString();
	std::string _rotationattri(TCHAR_TO_UTF8(*_rotationstr));
	TSharedPtr<FJsonObject> _jsonObj = MakeShareable(new FJsonObject);
	_jsonObj->SetStringField("location", _locationstr);
	_jsonObj->SetStringField("rotation", _rotationstr);
	_jsonObj->SetStringField("velocity", _velocity);
	_jsonObj->SetNumberField("movemode", GetCharacterMovement()->GetGroundMovementMode());
	FString _jsonAttribution;
	TSharedRef<TJsonWriter<TCHAR>> t_writer = TJsonWriterFactory<>::Create(&_jsonAttribution);
	FJsonSerializer::Serialize(_jsonObj.ToSharedRef(), t_writer);
	std::string _attribution(TCHAR_TO_UTF8(*_jsonAttribution));
	rti1516::AttributeHandleValueMap _attributeValueMap;
	rti1516::VariableLengthData tag = toVariableLengthData(_fedTypeName);
	_attributeValueMap[_characterAttributeHandle] = toVariableLengthData(_attribution);
	SintolRTI::SDKManager::GetInstance()->updateAttributeValues(_charactorObjInstance, _attributeValueMap, tag);
	SintolRTI::SDKManager::GetInstance()->Update(0.001);
	_charactorBehaviorTree.update(DeltaSeconds);
}

void AUnrealRTOSCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	try {
		SintolRTI::SDKManager::GetInstance()->deleteObjectInstance(_charactorObjInstance, toVariableLengthData("MultiAI_01"));
		SintolRTI::SDKManager::GetInstance()->unsubscribeObjectClass(_characterObjHandle);
	}
	catch (const rti1516::Exception& e) {
		std::wcout << L"rti1516::Exception: \"" << e.what() << L"\"" << std::endl;
		return;
	}
	catch (...) {
		std::wcout << L"Unknown Exception!" << std::endl;
		return;
	}
	SintolRTI::SDKManager::GetInstance()->StopSDK();
	SintolRTI::EntityManager::GetInstance()->Clear();
	_charactorBehaviorTree.clear();
	if (NULL != _ambassador)
	{
		delete _ambassador;
		_ambassador = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AUnrealRTOSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AUnrealRTOSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUnrealRTOSCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AUnrealRTOSCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AUnrealRTOSCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AUnrealRTOSCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AUnrealRTOSCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AUnrealRTOSCharacter::OnResetVR);
}


rti1516::VariableLengthData AUnrealRTOSCharacter::toVariableLengthData(const std::string& s)
{
	rti1516::VariableLengthData variableLengthData;
	variableLengthData.setData(s.data(), (unsigned long)s.size());
	return variableLengthData;
}

void AUnrealRTOSCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AUnrealRTOSCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AUnrealRTOSCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AUnrealRTOSCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUnrealRTOSCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AUnrealRTOSCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AUnrealRTOSCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
