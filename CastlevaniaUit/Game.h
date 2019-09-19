#pragma once
#include"GlobalObject.h"

class CGame {

private:
	LPDIRECTINPUT8 di;										// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;								// The keyboard device
	BYTE keyStates[256];									// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;
	HINSTANCE hInstance = NULL;						// hInstance của windows hiện tại
	HWND hWnd = NULL;								// hWnd hiện tại
	LPD3DXSPRITE spriteHandler = NULL;			// SpriteHanlder hiện tại
	LPDIRECT3DDEVICE9 d3ddev = NULL;				// Device directX hiện tại (nhằm đại diện card màn hình)
	LPDIRECT3DSURFACE9 backBuffer = NULL;		// BackBuffer

public:
	CGame(HWND hWnd);				
	void Init(HWND hWnd);			
	void LoadResources();
	void Run();						
	void Update(float dt);			
	void Render();					
	void ProcessKeyboard();



};