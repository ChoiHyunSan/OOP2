#pragma once
#include <conio.h>
#include "Utils.h"
#include <fstream>

using namespace std;

enum class KeyState
{
	Idle,
	Pressed,
	Stay,
	Released,
	PressedReleased
};

typedef KeyState MouseState;

class InputSystem
{
	KeyState keys[256];
	HANDLE hStdin;
	DWORD fdwSaveOldMode;
	INPUT_RECORD irInBuf[128];

	MouseState mouse[3];

	COORD mousePosition;
	
	ofstream log;

	VOID ErrorExit(LPCSTR lpszMessage)
	{
		fprintf(stderr, "%s\n", lpszMessage);

		// Restore input mode on exit.

		SetConsoleMode(hStdin, fdwSaveOldMode);

		ExitProcess(0);
	}

	VOID KeyEventProc(KEY_EVENT_RECORD ker)
	{
		Borland::GotoXY(0, 26);
		printf("KEYBD: ");
		log << endl << "MOUSE: " << GetTickCount64() << " ";

		switch (keys[ker.wVirtualKeyCode & 0x00ff])
		{
		case KeyState::Idle:
			if (ker.bKeyDown == TRUE)
				keys[ker.wVirtualKeyCode] = KeyState::Pressed;
			break;
		case KeyState::Pressed:
			if (ker.bKeyDown == FALSE)
				keys[ker.wVirtualKeyCode] = KeyState::PressedReleased;
			else 
				keys[ker.wVirtualKeyCode] = KeyState::Stay;
			break;
		case KeyState::Stay:
			if (ker.bKeyDown == FALSE)
				keys[ker.wVirtualKeyCode] = KeyState::Released;
			break;
		case KeyState::Released: 
		case KeyState::PressedReleased:
			keys[ker.wVirtualKeyCode] = KeyState::Idle;
			break;
		}
	}

	VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
	{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
		Borland::GotoXY(0, 28);
		printf("MOUSE: ");
		log << endl << "MOUSE: " << GetTickCount64() << " ";
		int mouseNo = -1;

		switch (mer.dwEventFlags)
		{
		case 0:

			if (mer.dwButtonState == (FROM_LEFT_1ST_BUTTON_PRESSED | RIGHTMOST_BUTTON_PRESSED)
				|| mer.dwButtonState == FROM_LEFT_2ND_BUTTON_PRESSED) {
				mouseNo = 2;
			}
			else if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				mouseNo = 0;
			}
			else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
				mouseNo = 1;
			}
			
			if (mouseNo == -1) {
				log << " other button pressed ";
				for (int i = 0; i < 3; i++)
				{
					switch (mouse[i]) {
					case MouseState::Stay:
						mouse[i] = MouseState::Released;
						mousePosition = mer.dwMousePosition;

						log << i << " [stay -> released]";
						break;
					}
				}
				break; /* return immediately */
			}
			
			
			log << mouseNo << " button pressed ";
			switch (mouse[mouseNo]) {
			case MouseState::Idle:
				if (mouseNo != 2 && (mouse[2] == MouseState::Pressed || mouse[2] == MouseState::Stay))
					break;
				mouse[mouseNo] = MouseState::Pressed;
				mousePosition = mer.dwMousePosition;
				log << mouseNo << " [idle -> pressed]";
				if (mouseNo == 2 && mouse[0] == MouseState::Pressed) {
					mouse[0] = MouseState::Idle;
					log << " 0 button state cancelled";
				}
				if (mouseNo == 2 && mouse[1] == MouseState::Pressed) {
					mouse[1] = MouseState::Idle;
					log << " 1 button state cancelled";
				}
				break;
			case MouseState::Pressed:
				if (mouseNo != 2 && (mouse[2] == MouseState::Pressed || mouse[2] == MouseState::Stay)) {
					mouse[mouseNo] = MouseState::Idle;
					log << mouseNo << " button state cancelled";
					break;
				}
				mouse[mouseNo] = MouseState::Stay;
				mousePosition = mer.dwMousePosition;
				log << mouseNo << " [pressed -> stayed]";
				break;
			}
			break;
		case DOUBLE_CLICK:
			printf("double click\n");
			break;
		case MOUSE_HWHEELED:
			printf("horizontal mouse wheel\n");
			break;
		case MOUSE_MOVED:
			mousePosition = mer.dwMousePosition;
			printf("mouse moved\n");
			break;
		case MOUSE_WHEELED:
			printf("vertical mouse wheel\n");
			break;
		default:
			printf("unknown\n");
			break;
		}
	}

public:
	InputSystem() : log("event.txt") {
		DWORD fdwMode;

		for (int i = 0; i < 256; i++)
			keys[i] = KeyState::Idle;

		mouse[0] = MouseState::Idle;
		mouse[1] = MouseState::Idle;
		mousePosition = { 0, 0 };

		memset(irInBuf, 0, sizeof(INPUT_RECORD) * 128);

		// Get the standard input handle.

		hStdin = GetStdHandle(STD_INPUT_HANDLE);
		if (hStdin == INVALID_HANDLE_VALUE)
			ErrorExit("GetStdHandle");

		// Save the current input mode, to be restored on exit.

		if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
			ErrorExit("GetConsoleMode");

		// Enable the window and mouse input events.

		fdwMode = (ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT) & ~ENABLE_QUICK_EDIT_MODE;
		if (!SetConsoleMode(hStdin, fdwMode))
			ErrorExit("SetConsoleMode");
	}


	virtual ~InputSystem() {
		SetConsoleMode(hStdin, fdwSaveOldMode);
		log.close();
	}

	void readEveryFrame() {
		DWORD cNumRead = 0;

		Borland::GotoXY(0, 25);
		if (GetNumberOfConsoleInputEvents(hStdin, &cNumRead) == 0)
		{
			printf("Input Reading Failure %d\n", GetLastError() );
			return;
		}

		for (int i = 0; i < 256; i++) {
			switch (keys[i]) {
			case KeyState::Released: 
			case KeyState::PressedReleased:
				keys[i] = KeyState::Idle; 
				break;
			case KeyState::Pressed:
				keys[i] = KeyState::Stay; 
				break;
			}
		}
		for (int i = 0; i < 3; i++) {
			switch (mouse[i]) {
			case MouseState::Released:
				log << endl << "FRAME: " << GetTickCount64() << " " << i << " button [released -> idle]";
				mouse[i] = MouseState::Idle;
				break;
			case MouseState::Pressed:
				mouse[i] = MouseState::Stay;
				log << endl << "FRAME: " << GetTickCount64() << " " << i << " button [pressed -> stay]";
				break;
			}
		}

		if (cNumRead == 0) {
			printf("cNumRead = %d (no event)\n", cNumRead);
			return;
		}
	
		if (!ReadConsoleInput(
			hStdin,      // input buffer handle
			irInBuf,     // buffer to read into
			128,         // size of read buffer
			&cNumRead)) // number of records read
			ErrorExit("ReadConsoleInput");
		
		printf("cNumRead = %d (event)   \n", cNumRead);
		for (int i = 0; i < (int)cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input
				KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;

			case MOUSE_EVENT: // mouse input
				MouseEventProc(irInBuf[i].Event.MouseEvent);
				break;
			}
		}
	}

	auto getKeyDown(WORD keyCode) const
	{
		printf("key state down [%x]\n", keys[keyCode & 0x00ff] );
		return keys[keyCode & 0x00ff] == KeyState::Pressed 
			|| keys[keyCode & 0x00ff] == KeyState::PressedReleased;
	}

	auto getKey(WORD keyCode) const
	{
		printf("key state stay [%x]\n", keys[keyCode & 0x00ff]);
		return keys[keyCode & 0x00ff] == KeyState::Pressed 
			|| keys[keyCode & 0x00ff] == KeyState::Stay 
			|| keys[keyCode & 0x00ff] == KeyState::PressedReleased 
			|| keys[keyCode & 0x00ff] == KeyState::Released;
	}
	
	auto getKeyUp(WORD keyCode) const
	{
		printf("key state up [%x]\n", keys[keyCode & 0x00ff]);
		return keys[keyCode & 0x00ff] == KeyState::Released 
			|| keys[keyCode & 0x00ff] == KeyState::PressedReleased;
	}

	auto getMouseButton(int button) const
	{
		printf("mouse state [%x]\n", mouse[button]);
		return mouse[button] == MouseState::Pressed 
			|| mouse[button] == MouseState::Stay 
			|| mouse[button] == MouseState::Released;
	}
	auto getMouseButtonDown(int button) const
	{
		printf("mouse state down [%x]\n", mouse[button]);
		return mouse[button] == MouseState::Pressed;
	}
	auto getMouseButtonUp(int button) const
	{
		printf("mouse state up [%x]\n", mouse[button]);
		return mouse[button] == MouseState::Released;
	}

	Position getMousePosition() const 
	{
		return { mousePosition.X, mousePosition.Y };
	}

};

