#include "pch.h"
#include <Windows.h>
#include "OsuMenuLayer.h"
#include "Mouse.h"

bool OsuMenuLayer::openedBefore = false;

DWORD WINAPI Main_Thread(void* hModule)
{
	if (MH_Initialize() != MH_OK)
	{
		FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(hModule), 0);
	}
#ifdef DEBUG
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
#endif
	CCTexture2D::setDefaultAlphaPixelFormat(kTexture2DPixelFormat_RGBA8888);
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x190550), OsuMenuLayer::create, NULL); // MenuLayer
	MH_EnableHook(MH_ALL_HOOKS);

	return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD _reason, LPVOID lpReserved)
{
	if (_reason == DLL_PROCESS_ATTACH)
	{
		CreateThread(0, 0x1000, Main_Thread, hModule, 0, 0);
	}

	return TRUE;
}

