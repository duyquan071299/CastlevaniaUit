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
	CAnimationDatabase::GetInstance()->LoadAnimation();
	CSceneManager::GetInstance()->LoadScene(new CPlayScene());
	CSceneManager::GetInstance()->GetCurrentScene()->Loadresources(0);
	
	
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
		DWORD now = GetTickCount();
		DWORD dt = now - frameStart;

		if(dt>=tickPerFrame)
		{
			frameStart = now;
			ProcessKeyboard();
			Update(dt);
			Render();
		}
		else
		{
			Sleep(tickPerFrame - dt);
		}
			
	}

	return;
}

void CGame::Update(DWORD dt) {
	//update scene here
	CSceneManager::GetInstance()->GetCurrentScene()->Update(dt);
}

void CGame::Render() {

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		if (CSimon::GetInstance()->isUsingCross)
		{
			D3DCOLOR color = rand() % 2 == 1 ? BACKGROUND_COLOR : BACKGROUND_COLOR_2;
			d3ddv->ColorFill(backBuffer, NULL, color);
		}
		else
			d3ddv->ColorFill(backBuffer, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		//Render scene here
		//CSpriteDatabase::GetInstance()->GetSprite(PLAYER)->Draw(100, 100, 255);
		CSceneManager::GetInstance()->GetCurrentScene()->Render();
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



	//->KeyState((BYTE *)&keyStates);
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


void CGame::SweptAABB(
	float ml, float mt, float mr, float mb,
	float dx, float dy,
	float sl, float st, float sr, float sb,
	float &t, float &nx, float &ny)
{

	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = -99999999999;
		tx_exit = 99999999999;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999;
		ty_exit = 99999999999;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}

}