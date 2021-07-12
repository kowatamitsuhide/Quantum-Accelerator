#include "C_MAIN.h"
#include "../SCENEMANAGER/SceneManager.h"

#include "../../ObjectPlacement/ObjectPlacement.h"
#include "../../C_MAP/C_MAP.h"
#include "../../C_SHADER/C_SHADER.h"
#include "../../ObstacleManager/ObstacleManager.h"
#include "../../../CMapMove.h"

void C_MAIN::Initialize(){

	auto&& c_mapmove = (new CMapMove());
	_objectroot.AddList((ChildObjRef)c_mapmove);

	GraphicsDevice.SetRenderState(Lighting_Disable);
	bgm = SoundDevice.CreateMusicFromFile(_T("BGM/bgm.wav"));
	bgm->Play();

	auto&& c_objectplacement = (new PlacementManager);
	_objectroot.AddList((ChildObjRef)c_objectplacement);

	auto&& c_obstaclemanager = (new ObstacleManager);
	_objectroot.AddList((ChildObjRef)c_obstaclemanager);

	auto&& c_map = new C_MAP;
	_objectroot.AddList((ChildObjRef)c_map);

	p_ugui = new CUI();
	_objectroot.AddList((ChildObjRef)p_ugui);
}

C_MAIN::~C_MAIN()
{

};

void C_MAIN::Update() {
	_objectroot.Update();

	if (p_ugui->game_over_flag){
		bgm->Stop();
		SceneManager::ChangeScene(SceneManager::GAME_OVER);
	}
	else if (p_ugui->clear_flag && p_ugui->game_over_flag == false) { clear_frame++; }
	if (clear_frame >= 120) { SceneManager::ChangeScene(SceneManager::RESULT); }

}

void C_MAIN::Draw3D()
{
	_objectroot.Draw3D();
}
void C_MAIN::Draw2D()
{
	_objectroot.Draw2D();
}
void C_MAIN::DrawAlpha3D() 
{
	GraphicsDevice.BeginAlphaBlend();

	_objectroot.DrawAlpha3D();

	GraphicsDevice.EndAlphaBlend();
};

void C_MAIN::DrawEnd()
{
	_objectroot.DrawEnd();
}

