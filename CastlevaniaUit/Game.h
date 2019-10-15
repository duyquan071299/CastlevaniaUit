#pragma once
#include"GlobalObject.h"
#include"TextureDatabase.h"
#include"SceneManager.h"
#include"SpriteDatabase.h"
#include"IntroScene.h"
#include"PlayScene.h"
#include"IntroScene.h"
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
	void Update(DWORD dt);			
	void Render();					
	void ProcessKeyboard();
	static void SweptAABB(
		float ml, float mt, float mr, float mb,
		float dx, float dy,
		float sl, float st, float sr, float sb,
		float &t, float &nx, float &ny);
	//int IsKeyDown();
	~CGame(){}



};