#pragma once

#include<Windows.h>

bool IsKeyDown(int VirtualKeyCode)
{
	short KeyState = GetAsyncKeyState(VirtualKeyCode);
	return((KeyState & 0x8000) > 0);
}