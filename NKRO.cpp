#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <WinUser.h>

LRESULT CALLBACK nkro(int code, WPARAM wParam, LPARAM lParam)
{
	int KeyTotalPress = 0;

	int KeyPressA = 0;
	int KeyPressB = 0;
	int KeyPressC = 0;
	int KeyPressD = 0;

	bool lastKeyPressA = false;
	bool lastKeyPressB = false;
	bool lastKeyPressC = false;
	bool lastKeyPressD = false;

	double KeyPressCount = 0;

	while (1)
	{
		for (;;)
		{
			WORD state1 = GetAsyncKeyState(0x57);									// W		Ű ���� �б�.
			WORD state2 = GetAsyncKeyState(0x41);									// A		
			WORD state3 = GetAsyncKeyState(0x53);									// S		
			WORD state4 = GetAsyncKeyState(0x44);									// D		


			KeyPressA = 0 != (state1 & 0x8000);										// 		Ű ����, �ȴ��� Ȯ��.  
			KeyPressB = 0 != (state2 & 0x8000);										// 
			KeyPressC = 0 != (state3 & 0x8000);										// 
			KeyPressD = 0 != (state4 & 0x8000);										// 

			KeyTotalPress = KeyPressA + KeyPressB + KeyPressC + KeyPressD;

			if (KeyPressA && KeyTotalPress <= 2)									// 		Ű ���� �ΰ�?
			{
				if (!lastKeyPressA)													// 		���� ���°� �ȴ��� �ΰ�?
				{
					KeyPressCount++;												// 		���� �ٲ�����Ƿ�, 1ȸ ����.
				}
			}

			if (KeyPressB && KeyTotalPress <= 2)									// 		Ű ���� �ΰ�?
			{
				if (!lastKeyPressB)													// 		���� ���°� �ȴ��� �ΰ�?
				{
					KeyPressCount++;												// 		���� �ٲ�����Ƿ�, 1ȸ ����.
				}
			}

			if (KeyPressC && KeyTotalPress <= 2)									// 		Ű ���� �ΰ�?
			{
				if (!lastKeyPressC)													// 		���� ���°� �ȴ��� �ΰ�?
				{
					KeyPressCount++;												// 		���� �ٲ�����Ƿ�, 1ȸ ����ww
				}
			}

			if (KeyPressD && KeyTotalPress <= 2)									// 		Ű ���� �ΰ�?
			{
				if (!lastKeyPressD)													// 		���� ���°� �ȴ��� �ΰ�?
				{
					KeyPressCount++;												// 		���� �ٲ�����Ƿ�, 1ȸ ����.
				}
			}

			lastKeyPressA = KeyPressA;												// 		Ű ���� ���.
			lastKeyPressB = KeyPressB;												// 
			lastKeyPressC = KeyPressC;												//
			lastKeyPressD = KeyPressD;												// w

			if (KeyTotalPress > 2)
			{
				break;
			}

			printf("KeyState=%d KeyCount=%f\n", KeyTotalPress, KeyPressCount);		// ���.
		}
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}

int main()
{
	HHOOK keyboardHook = 0;

	keyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, nkro, GetModuleHandleA(NULL), 0);

	if (keyboardHook == 0)
	{
		printf("Failed\n");
		return -1;
	}
	printf("OK\n");

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(keyboardHook);

	return 0;
}
