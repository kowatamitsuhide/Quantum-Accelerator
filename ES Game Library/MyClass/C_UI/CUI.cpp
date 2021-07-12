#include "CUI.h"
#include"../INFORMATION/INFORMATION.h"
#include "../ALL_SCENE/SCENEMANAGER/SceneManager.h"
#include <algorithm>

int CUI::total;

CUI::CUI()
{
	//!自分をリストに登録
	observer.addListener(this);
}

CUI::~CUI()
{
	//!自分をリストから削除
	observer.removeListener(this);
}

void CUI::Init()
{
	speed_gage = sprite_mng.CreateSpriteFromFileRect(_T("UI/speedgage/sp.png"),  Vector3(0.0f, 0.0f, 0.0f));

	sprite_mng.CreateSpriteFromFile(_T("SPRITE/aka.png"), Vector3(0.0f, 0.0f, SpriteBatch_BottomMost));

	black_out = sprite_mng.CreateSprite(Vector2(1280.0f, 720.0f), Color(0, 0, 0), Vector3(0.0f,0.0f, SpriteBatch_TopMost));

	AddFontResourceEx(_T("font/thirteen-pixel-fonts/thirteen_pixel_fonts.ttf"), FR_PRIVATE, nullptr);
	font      = GraphicsDevice.CreateSpriteFont(_T("Thirteen Pixel Fonts"), 90);

	//!スコア関係の初期化
	game_timer = MAX_TIMER;
	gate_count = FIRST_GATE;

	for (int i = FIRST_GATE; i <= SECOND_GATE; i++) { gate_score[i]; }

	IUiParametor::Instance().CreateParametor("ui");
	_ui_data.reset(new UiData);
}
 
void CUI::Update()
{	
	if (black_out_flag) { if (sprite_mng.BlackOutTrigger(black_out)) { game_over_flag = true; }; };

	if (this->FrameTimeObsever(60)) {SetGateParameter(-1);};

	if (game_timer <= 0) { OnCollision("GAMEOVER"); };

}

void CUI::Draw2D()
{
	sprite_mng.SetRectWH(speed_gage, 192 * _ui_data->GetSpeedMeterParams("ui"), 0, 192, 192);

	game_timer = this->clamp(game_timer, 0, MAX_TIMER);
	SpriteBatch.DrawString(font, Vector2(600.0f, 0.0f), Color(255, 255, 255), _T("%d"), game_timer);

	sprite_mng.DrawSprite();
}

void CUI::OnCollision(std::string collsion_tag)
{
	if (collsion_tag == "DAMAGE") { 
		CollisionTypeDamage();    return;
	};
	if (collsion_tag == "RECOVERY") {
		CollisionTypeRecovery();  return;
	};
	if (collsion_tag == "GAMEOVER") {
		CollisionTypeGameOver();  return;
	};
	if (collsion_tag == "ITEMBROCK") {
		CollisionTypeItemBrock(); return;
	};
	if (collsion_tag == "GATEBREAK") {
		CollisionTypeGateBreak(); return;
	};
	ASSERT(FALSE && "衝突判定のタグ名が違います。");
}

void CUI::CollisionTypeDamage()
{
	SetGateParameter(-3);

	_ui_data->SetSpeedMeterParams("ui", -1);
}

void CUI::CollisionTypeRecovery()
{
	_ui_data->SetSpeedMeterParams("ui",  1);
}

void CUI::CollisionTypeGameOver()
{
	black_out_flag = true;
}

void CUI::CollisionTypeItemBrock()
{
	SetGateParameter( 2);
}

void CUI::CollisionTypeGateBreak()
{
	//!ゲートを超えたらスコアを加算する
	switch (gate_count) {
	case FIRST_GATE:
		gate_score[FIRST_GATE] = game_timer * 100;
		break;
	case SECOND_GATE:
		gate_score[SECOND_GATE] = game_timer * 100;
		break;
	case THIRD_GATE:
		gate_score[THIRD_GATE] =  game_timer * 100;
		total = gate_score[FIRST_GATE] + gate_score[SECOND_GATE] + gate_score[THIRD_GATE];
		clear_flag = true;
		break;
	}
	
	gate_count++;
	SetGateParameter(20);
}

void CUI::SetGateParameter(int gate_numbers = 1)
{
	this->gagefcomveter += (MAX_TIMER * 0.1f) * gate_numbers;
	this->game_timer    +=                      gate_numbers;
	this->
	_ui_data->SetGageParams("ui", gagefcomveter);
}

