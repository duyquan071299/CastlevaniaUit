﻿#pragma once
#include"GlobalObject.h"
#include"TextureFactory.h"
#include"SpriteFactory.h"

class CGame {

private:
	LPDIRECTINPUT8 di;										// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;								// The keyboard device
	BYTE keyStates[256];									// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	

	

public:
	CGame(HWND hWnd);				
	void Init(HWND hWnd);			
	void LoadResources();
	void Run();						
	void Update(float dt);			
	void Render();					
	void ProcessKeyboard();



};