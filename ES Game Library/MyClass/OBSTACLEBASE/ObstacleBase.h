#pragma once
#include "../C_OBJECT/Object.h"
#include "../../ESGLib.h"
#include "../C_HITBOX/HitBox.h"
#include "../CPLAYERDATA/CPlayerData.h"
#include "..//OBSEVER/OBSEVER.h"
#include "../MapPlacementData/MapPlacementData.h"
#include "../UIDATABASE/UiDataBase.h"
#include "../CCHARACTER/Character.h"


struct MODEL_PARAMETERS
{
public:
	Vector3 p_model_position_revision  = Vector3(0.0f,0.0f,0.0f);
	Vector3 p_hitbox_position_revision = Vector3(0.0f,0.0f,0.0f);

	char    tags = '?';

private:
};

enum ATTACK_TYPE {DAMEGE,ITEM,GAMEOVER,ITEMBROCK,END};

struct ATTACK_PARAMETERS
{
public:
	//与えるダメージ量
	float _AddDamege = 0.0f;
	//属性
	ATTACK_TYPE _Type;
private:
};

class ObstacleBase : public Object
{
public:
	ObstacleBase();
	virtual ~ObstacleBase() {};

	virtual void Init()        override = 0;
	virtual void Update()      override = 0;
	virtual void Draw3D()      override;

	virtual void DrawAlpha3D() override { return; };
	virtual void Draw2D()      override { return; };

	ATTACK_PARAMETERS GetAttackParameters() const { return attack_parameters; };
private:

protected:
	//関数宣言

	bool         OnCollsion();
	virtual void IsCollsion() { return; };

	virtual bool PModelParameter(std::vector<Vector3>::iterator& itr) { return false; };

	ATTACK_PARAMETERS attack_parameters;
	MODEL_PARAMETERS   model_parameters;

	//変数宣言
	HitBox*   p_hitbox;
	Model     p_model;
	OBSERVER* p_obsever;

	float p_distance;

	//プレイヤーのデータベース
	std::unique_ptr<IMapData>     _imap_data;
	std::unique_ptr<UiData>       _iui_data;
	std::unique_ptr<IPlayerData>  _iplayer_data;
};