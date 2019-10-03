#pragma once
#include "Scene.h"

class CSceneManager
{
private:
	static CSceneManager * instance;
	CScene * currentScene;
	

	bool isChangeScene;
public:

	static CSceneManager * GetInstance();
	CSceneManager();
	CScene * GetCurrentScene();

	~CSceneManager();

	bool IsChangeScene() { return this->isChangeScene; }
	void SetChangeScene(bool change = true) { this->isChangeScene = change; }

	void LoadScene(CScene * newScene);

	void Update(DWORD dt);
};

