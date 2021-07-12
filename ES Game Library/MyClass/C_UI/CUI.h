#pragma once
#include "../C_OBJECT/Object.h"
#include "../../ESGLib.h"
#include"../OBSEVER/OBSEVER.h"

#include "../CSHAREDMETHOD/CSharedMethod.h"
#include "../C_SPRITE/C_Sprite.h"
#include "../C_UI/CUI.h"
#include "../UIDATABASE/UiDataBase.h"

#include "../CPLAYERDATA/CPlayerData.h"

class CUI : public Object, OBSERVERLISTENER, CSharedMethod
{
public:

	CUI();
	~CUI();

	virtual void Init()        override;
	virtual void Update()      override;
	virtual void Draw3D()      override { return; };

	virtual void DrawAlpha3D() override { return; };
	virtual void Draw2D()      override;
	
	//オブザーバー関数
	virtual void CUI::OnCollision(std::string collsion_tag)     override;

	virtual void CUI::CollisionTypeDamage();
	virtual void CUI::CollisionTypeRecovery();
	virtual void CUI::CollisionTypeGameOver();
	virtual void CUI::CollisionTypeItemBrock();
	virtual void CUI::CollisionTypeGateBreak();

	void CUI::SetGateParameter(int gate_numbers);

	bool game_over_flag = false;
	bool clear_flag     = false;
	static int total;

private:
	OBSERVER      observer;
	SpriteManager sprite_mng;

	int gage;
	int speed_gage;
	int black_out;

	FONT  font;
	int game_timer;
	int MAX_TIMER = 30;
	int gagefcomveter = 100;

	bool black_out_flag = false;

	//!プレイヤーのデータベース
	std::unique_ptr<UiData>        _ui_data;


	/**
　　* @enum Gates
　　* ゲート通過時のスコア加算用
　　*/
	enum Gates {FIRST_GATE,SECOND_GATE,THIRD_GATE};
	int gate_count;    //!通過したゲートの個数
	int gate_score[3]; //!スコアの配列


};