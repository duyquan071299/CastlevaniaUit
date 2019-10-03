#include "SceneManager.h"

CSceneManager * CSceneManager::instance = NULL;

CSceneManager::CSceneManager()
{

}

CSceneManager::~CSceneManager()
{
}

CSceneManager * CSceneManager::GetInstance()
{
	if (!instance)
	{
		instance = new CSceneManager();
	}
	return instance;
}


void CSceneManager::Update(DWORD dt)
{
	currentScene->Update(dt);
}


void CSceneManager::LoadScene(CScene * newScene)
{
	delete this->currentScene;
	this->currentScene = newScene;
}

CScene * CSceneManager::GetCurrentScene()
{
	return this->currentScene;
}
