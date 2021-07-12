#include"SceneManager.h"
#include "../TITLE/C_TITLE.h"
#include "../MAIN/C_MAIN.h"
#include "../GAME_OVER/C_GAME_OVER.h"
#include "../GAME_CLEAR/GAEM_CLEAR.h"
#include "../Result/Result.h"

BaseScene *SceneManager::m_pScene = nullptr;

void SceneManager::ChangeScene(SCENE scene) {

	if (m_pScene != nullptr) {
		delete m_pScene;
	}
	switch (scene) {          
	case SCENE::TITLE:
		m_pScene = new C_TITLE;
		break;
	case SCENE::RESULT:
		m_pScene = new C_RESULT;
		break;
	case SCENE::MAIN:
		m_pScene = new C_MAIN;
		break;
	case SCENE::GAME_OVER:
		m_pScene = new C_GAME_OVER;
		break;
	case SCENE::GAME_CLEAR:
		m_pScene = new GAEM_CLEAR;
		break;
	}
	m_pScene->Initialize();
}

void SceneManager::Update() {
	m_pScene->Update();       
}

void SceneManager::Draw3D() {
	m_pScene->Draw3D();           
}

void SceneManager::DrawAlpha3D() {
	m_pScene->DrawAlpha3D();
}

void SceneManager::DrawEnd()
{
	m_pScene->DrawEnd();
}

void SceneManager::Draw2D() {
	m_pScene->Draw2D();
}
