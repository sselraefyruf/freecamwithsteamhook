#pragma once

struct FVector
{
	float X;
	float Y;
	float Z;
};

struct FRotator
{
	float Pitch;
	float Yaw; 
	float Roll;
};

enum EStereoscopicPass
{
	eSSP_FULL,
	eSSP_LEFT_EYE,
	eSSP_RIGHT_EYE,
	eSSP_LEFT_EYE_SIDE,
	eSSP_RIGHT_EYE_SIDE,
};

class FMinimalViewInfo
{
public:
	FVector Location; 
	FRotator Rotation;
	float FOV; 
	float DesiredFOV; 
	float OrthoWidth; 
	float OrthoNearClipPlane; 
	float OrthoFarClipPlane; 
	float AspectRatio;
};

class UWorld {
public:
	char pad_0000[0x180];
	class UGameInstance* OwningGameInstance; 
};

class UGameInstance {
public:
	char pad_0000[0x38];
	class LocalPlayer* LocalPlayer;
};

class LocalPlayer {
public:
	class LocalPlayers* LocalPlayers;
};

class LocalPlayers {
public:
	char pad_0000[0x30];
	class APlayerController* PlayerController;
};

