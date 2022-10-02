// dllmain.cpp : Defines the entry point for the DLL application.
#include "UE.h"
#include "util.h"

void(*OGetViewPoint)(LocalPlayer*, FMinimalViewInfo*, EStereoscopicPass) = nullptr;

void GetViewPoint(LocalPlayer* thisLocalPlayer, FMinimalViewInfo* OutViewInfo, EStereoscopicPass StereoPass)
{
	// Call original function setting OutViewInfo (Before modifying it)
	OGetViewPoint(thisLocalPlayer, OutViewInfo, StereoPass);

	static bool GetCameraLocation = true;
	static FVector NewLocation;

	if (GetCameraLocation) {
		// Set our new location to the original spot once
		NewLocation = OutViewInfo->Location;
		GetCameraLocation = false;
	}

	if (GetAsyncKeyState('W') & 1) NewLocation.X += 75.f;
	else if (GetAsyncKeyState('S') & 1) NewLocation.X -= 75.f;
	else if (GetAsyncKeyState('A') & 1) NewLocation.Y += 75.f;
	else if (GetAsyncKeyState('D') & 1) NewLocation.Y -= 75.f;
	else if (GetAsyncKeyState(VK_SPACE) & 1) NewLocation.Z += 75.f;
	else if (GetAsyncKeyState(VK_SHIFT) & 1) NewLocation.Z -= 75.f;

	// Modify OutViewInfo
	OutViewInfo->Location = NewLocation;
}

void hook(__int64 addr, __int64 func, __int64* orig)
{
	// this hook works only on steam games
    static uintptr_t hook_addr;
    if (!hook_addr)
        hook_addr = SignatureScan("GameOverlayRenderer64.dll", "48 ? ? ? ? 57 48 83 EC 30 33 C0");

    auto hook = ((__int64(__fastcall*)(__int64 addr, __int64 func, __int64* orig, __int64 smthng))(hook_addr));
    hook((__int64)addr, (__int64)func, orig, (__int64)1);
}

void hookerayinamcigi() {

    auto odynxre_olsun = SignatureScan(NULL, "4C 8B DC 53 55 56 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 4D 89 7B D8");
    hook(odynxre_olsun, (__int64)GetViewPoint, (__int64*)&OGetViewPoint);
}

bool __stdcall DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(hModule);
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		hookerayinamcigi();
	}

	return TRUE;
}

