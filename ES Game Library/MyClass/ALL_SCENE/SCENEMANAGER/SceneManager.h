#pragma once
#include"BaseScreen.h"

class SceneManager {
public:
	static enum SCENE 
	{
		TITLE,
		RESULT,
		MAIN,
		GAME_OVER,
		GAME_CLEAR,
	};

	static void ChangeScene(SCENE scene);
	static void Update();
	static void Draw3D();
	static void Draw2D();
	static void DrawAlpha3D();
	static void DrawEnd();

	static BaseScene *m_pScene;

	static int index;
	
private:
	
};

