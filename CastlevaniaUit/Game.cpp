#include"Game.h"


CGame::CGame(HWND hWnd){
	this->Init(hWnd);
	this->LoadResources();
}

void CGame::Init(HWND hWnd)
{
	//Init library and back-buffer
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	// retrieve Window width & height to create back buffer
	RECT r;
	GetClientRect(hWnd, &r);	
	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	//create new device
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);
	if (d3ddv == NULL)
	{
		OutputDebugString("[ERROR] CreateDevice failed\n");
		return;
	}

	//get buffer
	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	//create Keyboard input

	HRESULT hr = DirectInput8Create(
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);
	if (hr != DI_OK)
	{
		OutputDebugString("[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK)
	{
		OutputDebugString("[ERROR] CreateDevice failed!\n");
		return;
	}
	hr = didv->SetDataFormat(&c_dfDIKeyboard);
	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		OutputDebugString("[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}


	OutputDebugString("[INFO] InitGame done;\n");


}


void CGame::LoadResources() {
	CTextureDatabase::GetInstance()->LoadTextures();
	CSpriteDatabase::GetInstance()->LoadResources();
	CSceneManager::GetInstance()->LoadScene(new CIntroScene);
	//CSpriteDatabase::GetInstance()->GetSprite(PLAYER)->Draw(100, 100, 0);
	
}
void CGame::Run() {
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;
		
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			Render();
	}

	return;
}

void CGame::Update(float dt) {
	//update scene here
	//scene -> update...
}
void CGame::Render() {

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(backBuffer, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		//Render scene here
		//CSpriteDatabase::GetInstance()->GetSprite(PLAYER)->Draw(100, 100, 255);
		CSceneManager::GetInstance()->GetCurrentScene()->Loadresources();
		//scene render.....
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);

}
void CGame::ProcessKeyboard() {
	HRESULT hr;

	// Collect all key states first
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
				OutputDebugString("[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			OutputDebugString("[ERROR] DINPUT::GetDeviceState failed. Error: %d\n");
			return;
		}
	}

	//keyHandler->KeyState((BYTE *)&keyStates);
	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		OutputDebugString("[ERROR] DINPUT::GetDeviceData failed. Error: %d\n");
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
		{
			CSceneManager::GetInstance()->GetCurrentScene()->OnKeyDown(KeyCode);
		}
		else
		{
			CSceneManager::GetInstance()->GetCurrentScene()->OnKeyUp(KeyCode);
		}
	}
}