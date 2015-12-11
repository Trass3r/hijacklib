#include "stdafx.h"
#include "hookfunction.h"

static DWORD WINAPI
MyGetVersion()
{
	return 0x0A28 << 16 | 0x0105; // XP, 5.1
}

constexpr auto OrgWndProc = (int (WINAPI *)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)) 0x005AF590;
constexpr auto OrgWndProcWindowed = (int (WINAPI *)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)) 0x00552EA0;
static bool renderingPaused = false;

LRESULT CALLBACK MyWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
//	case WM_ACTIVATE: // 6
//	case WM_CLOSE: // 0x0010
//	case WM_SYSCOMMAND: // 0x112
	case WM_KILLFOCUS:
		// Minimizes the specified window and activates the next top - level window in the Z order.
		ShowWindow(hWnd, SW_MINIMIZE);
		break;
	case WM_ACTIVATEAPP:
		if (wParam)
		{
			renderingPaused = false;
			OutputDebugStringA("Resumed Render\n");
		}
		else
		{
			renderingPaused = true;
			OutputDebugStringA("Paused Render\n");
		}
		break;
	case WM_MOUSEMOVE:
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}
	if (renderingPaused && msg <= 0x2FF)
		return DefWindowProcW(hWnd, msg, wParam, lParam);

	return OrgWndProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK MyWndProcWindowed(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
/*
	switch (msg)
	{
	case WM_ACTIVATE: // 6
	case WM_CLOSE: // 0x0010
	case WM_SYSCOMMAND: // 0x112
	case WM_KILLFOCUS:
		// Minimizes the specified window and activates the next top - level window in the Z order.
		ShowWindow(hWnd, SW_MINIMIZE);
		break;
	case WM_ACTIVATEAPP:
		if (wParam)
		{
			renderingPaused = false;
			OutputDebugStringA("Resumed Render\n");
		}
		else
		{
			renderingPaused = true;
			OutputDebugStringA("Paused Render\n");
		}
		break;
	case WM_MOUSEMOVE:
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}
	if (renderingPaused && msg <= 0x2FF)
		return DefWindowProcW(hWnd, msg, wParam, lParam);
*/
	return OrgWndProcWindowed(hWnd, msg, wParam, lParam);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                       )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		replaceFn(0x0066C10C, &MyGetVersion);
		// directly inject into RegisterClass param
		overWriteMem(0x005AF510 + 4, &MyWndProc);
		// directly inject into RegisterClassEx param
		//replaceFn(0x00552530 + 4, &MyWndProcWindowed);
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

