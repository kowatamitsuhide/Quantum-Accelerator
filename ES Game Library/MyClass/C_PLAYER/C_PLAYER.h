#pragma once
#include "../../ESGLib.h"
#include "../C_STATE/C_STATE.h"
#include "../C_OBJECT/Object.h"
#include "../c_Hitbox/HitBox.h"
#include "../CSHAREDMETHOD/CSharedMethod.h"
#include "../CCHARACTER/Character.h"
#include "../CPLAYERDATA/CPlayerData.h"
#include "../../Velocity.h"
#include "../../RotationMove.h"
#include "../../EnumManager.h"
#include "../C_EFFEKSEER/EffekseerMng.h"
#include "../C_DIS/C_DIS.h"
#include "../UIDATABASE/UiDataBase.h"
#include "../../AccelaretorBase.h"
#include "../HitStop/HitStop.h"
#include "../OBSEVER/OBSEVER.h"
#include "../C_CAMERA/C_CAMERA.h"

class CPlayerStateProcessor;
class CPlayer;

class ObstacleBase;

class CPlayerStateProcessor : public  StateProcessor {
public:
	CPlayer* p_player;
};

class CPlayer : public Object, CSharedMethod
{
private:
	//変数宣言
	MODEL            p_model     = nullptr;
	RotationMove*    p_rotation  = nullptr;
	HitBox*          p_hitbox    = nullptr;
	Velocity*        p_velocity  = nullptr;
	EffekseerMng*    p_effekseer = nullptr;
	HitStop*         p_hitstop   = nullptr;
	OBSERVER*        p_obsever   = nullptr;
	CCamera_*        p_camera    = nullptr;

	AccelaretorFront*     accelaretors = nullptr;

	Accelaretor_Parameter accelaretor_parameter[ACCELARETOR_TYPE::_END];

	int   state_type = -1;
	int  _accelaretor_type = 0;

	EFFECT shader  = nullptr;
	int    alpha   = 1; 
	int    color_r = 0;

	//プレイヤーのデータベース
	std::unique_ptr<IPlayerData>   _iplayer_data;
	std::unique_ptr<UiData>        _ui_data;

public:
	CPlayerStateProcessor p_state_processor;

	CPlayer(Vector3  _pos);
	virtual ~CPlayer();

	virtual void CPlayer::Init()        override;
	virtual void CPlayer::Update()      override;
	virtual void CPlayer::Draw3D()      override { return; };

	virtual void CPlayer::DrawAlpha3D() override;
	virtual void CPlayer::Draw2D()      override { return; };

	void AttackHit(ObstacleBase* attack_parameters);
	void MyCameraSetFieldOfViewY(float pov) { p_camera->SetCameraAngle(pov); };
private:
	int test_flg;
	class NOMAL : public State
	{
	private:
		CPlayerStateProcessor* _owner;
	public:
		NOMAL(CPlayerStateProcessor* owner) : _owner(owner) { };
		virtual ~NOMAL() {};
		virtual void Update() override;
	};

	class ROTATION : public State
	{
	private:
		CPlayerStateProcessor* _owner;
	public:
		ROTATION(CPlayerStateProcessor* owner) : _owner(owner) {}
		virtual ~ROTATION() {}
		virtual void Update() override;
	};

	class DAMAGE : public State
	{
	private:
		CPlayerStateProcessor* _owner;
	public:
		DAMAGE(CPlayerStateProcessor* owner);
		virtual ~DAMAGE() {};

		virtual int    CancelLv() { return INT_MAX; };
		virtual int    ExitTime() { return 30; };

		virtual void Update() override;
	};

	class IDOL : public State
	{
	private:
		CPlayerStateProcessor* _owner;
	public:
		IDOL(CPlayerStateProcessor* owner);
		virtual ~IDOL() {};
		virtual void Update() override;
	};

	class RECOVERY : public State
	{
	private:
		CPlayerStateProcessor* _owner;
	public:
		RECOVERY(CPlayerStateProcessor* owner);
		virtual ~RECOVERY() {};

		virtual int  ExitTime() { return 20; };

		virtual void Update() override;
	};

	void ChangeMoveType(PLAYER::PLAYERMOVETYPE move_type);
	void SetAccelaretorParameter(bool flag);
	void SetAccelaretor(int accelaretor_type);

	int  GetGiaLevel();
};