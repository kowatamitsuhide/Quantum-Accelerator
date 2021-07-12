#include "C_PLAYER.h"
#include "../C_SHADER/C_SHADER.h"
#include "../../C_Tonnel.h"
#include "../../CMapMove.h"
#include "../OBSTACLEBASE/ObstacleBase.h"

CPlayer::CPlayer(Vector3  _pos)
{
	transform.position = (_pos);
	this->transform.rotation.y += 180;
};

void CPlayer::Init()
{
	//オリジナルのプレイヤークラスにアクセス用
	p_state_processor.p_player = this;
	p_state_processor.ChangeState(new CPlayer::NOMAL(&p_state_processor));

	p_model = GraphicsDevice.CreateModelFromFile (_T("jiki_car//jiki_car3_a.X"));
	shader  = GraphicsDevice.CreateEffectFromFile(_T("FX//ShaderPlayer.hlsl"));

	SPRITE texture = GraphicsDevice.CreateSpriteFromFile(_T("jiki_car//jiki_car3.png"));
	shader->SetTexture("modelTex1", *texture);

	this->SetAccelaretorParameter(0.5f);

	p_hitbox = new HitBox();
	this->ChildObj_AddList((ChildObjRef)p_hitbox);	
	p_hitbox->Settags("player");
	p_hitbox->transform.localposition.y += 0.1f;

	auto&& c_distance = new C_Distance();
	this->ChildObj_AddList((ChildObjRef)c_distance);
	c_distance->IsTagSet("player");

	accelaretors = new AccelaretorFront();
	accelaretors->SetAccelaretorParameter(accelaretor_parameter[ACCELARETOR_TYPE::NOMAL]);
	this->ChildObj_AddList((ChildObjRef)accelaretors);

	p_hitstop = new HitStop();
	this->ChildObj_AddList((ChildObjRef)p_hitstop);
	p_hitstop->SetTaget(this);

	p_camera = (new CCamera_);
	this->ChildObj_AddList((ChildObjRef)p_camera);
	p_camera->gameObject = this;

	CShaderAnimation::CameraSetting(*p_camera);
	IPlayerParametor::Instance().CreateParametor("player");

	_iplayer_data.reset(new IPlayerData);
	_ui_data.reset(new UiData);
	
}

CPlayer::~CPlayer()
{
	
};

void CPlayer::Update()
{
	this->p_state_processor.Update();

	if (gameObject->gameObject == nullptr) { ChangeMoveType(PLAYER::PLAYERMOVETYPE::NOMAL);}
	else 
	if (typeid(*gameObject->gameObject) == typeid(C_Tonnel)){ ChangeMoveType(PLAYER::PLAYERMOVETYPE::ROTATION); };
}

void CPlayer::DrawAlpha3D()
{
	p_model->SetPosition(this->transform.position);

	//データベース更新
	_iplayer_data->SetPlayerPosition("player", this->transform.position);

	p_model->SetRotation(transform.rotation);

	auto&& itr = this->p_childObjects.rbegin();
	if (typeid(*((*itr).get())) == typeid(RotationMove)) {p_model->SetDirection(transform.direction);}

	shader->SetTechnique("Sobel");
	Matrix world    = p_model->GetWorldMatrix();
	Matrix viewproj = CShaderAnimation::camera->GetCamera().GetViewProjectionMatrix();
	shader->SetParameter("wvp", world * viewproj);

	shader->SetParameter("alpha",alpha); shader->SetParameter("r_color", color_r);

	p_model->Draw(shader);
}

void CPlayer::ChangeMoveType(PLAYER::PLAYERMOVETYPE move_type)
{
	if (state_type == move_type) return; else 	state_type = move_type;

	auto&& itr = p_childObjects;
	auto& obstacle_itr   = itr.begin();
	while (obstacle_itr != itr.end())
	{
		if (typeid(*((*obstacle_itr).get())) == typeid(RotationMove) || typeid(*((*obstacle_itr).get())) == typeid(Velocity))
		{
			obstacle_itr = itr.erase(obstacle_itr);
			continue;
		}
		obstacle_itr++;
	}
	switch (move_type)
	{
		case PLAYER::PLAYERMOVETYPE::NOMAL:
		p_velocity = new Velocity();	
		this->ChildObj_AddList((ChildObjRef)p_velocity);
	                                                	p_velocity->gameObject = this;
		break;
		case PLAYER::PLAYERMOVETYPE::ROTATION:
		p_rotation = new RotationMove();
		this->ChildObj_AddList((ChildObjRef)p_rotation);
                                                        p_rotation->gameObject = this;
		break;
	default:
		break;
	}
}

void CPlayer::SetAccelaretorParameter(bool flag)
{
	for (int i = 0; i < ACCELARETOR_TYPE::_END; i++)
	{
		accelaretor_parameter[i]._max_velocity = 0.30f + i * 0.05f;
		accelaretor_parameter[i]._min_velocity = 0.25f + i * 0.05f;
		accelaretor_parameter[i]._start_velocity = 0.2f + i * 0.1f;
		
	}




	if (flag) return;

	for (int i = 0; i < ACCELARETOR_TYPE::_END; i++) { accelaretor_parameter[i]._start_velocity = 0; };
}

int CPlayer::GetGiaLevel()
{
	auto&& speed_meter = _ui_data->GetSpeedMeterParams("ui");

	int NomaL = 3, Row = 6, Medium = 8;

	if (speed_meter <= NomaL)                                return ACCELARETOR_TYPE::NOMAL;
	if (speed_meter >= NomaL  + 1 && speed_meter <= Row)     return ACCELARETOR_TYPE::ROW; 
	if (speed_meter >= Row    + 1 && speed_meter <= Medium)  return ACCELARETOR_TYPE::MEDIUM;
	if (speed_meter >= Medium + 1)                           return ACCELARETOR_TYPE::HARD;
}

void CPlayer::SetAccelaretor(int accelaretor_type)
{
	if (_accelaretor_type == accelaretor_type) return; else 	_accelaretor_type = accelaretor_type;

	if (accelaretors != nullptr) { accelaretors->Remove(); };

	accelaretors = new AccelaretorFront();
	accelaretors->SetAccelaretorParameter(accelaretor_parameter[accelaretor_type]);
	                                                                       this->ChildObj_AddList((ChildObjRef)accelaretors);
}

void CPlayer::AttackHit(ObstacleBase* attack_parameters)
{
	if (p_effekseer != nullptr) { p_effekseer->Remove(); };

	p_effekseer = new EffekseerMng();
	this->ChildObj_AddList((ChildObjRef)p_effekseer);
	p_effekseer->transform.localscale = 0.1f;

	switch (attack_parameters->GetAttackParameters()._Type)
	{

	case ATTACK_TYPE::DAMEGE:
		SetAccelaretorParameter(0.0f);
		/*p_obsever->IsCollision("GAMEOVER");*/
		p_state_processor.ChangeState(new CPlayer::DAMAGE(&p_state_processor));
		break;
	case ATTACK_TYPE::ITEM:
		SetAccelaretorParameter(0.0f);
		p_state_processor.ChangeState(new CPlayer::RECOVERY(&p_state_processor));
		break;
	case ATTACK_TYPE::GAMEOVER:
		p_hitstop->SetStopCount(100);
		p_obsever->IsCollision("GAMEOVER");
		break;
	case ATTACK_TYPE::ITEMBROCK:
		SetAccelaretorParameter(0.0f);
		/*p_effekseer->PlayEffekseer(PLAYER::ITEMBROCK);*/
		p_state_processor.ChangeState(new CPlayer::RECOVERY(&p_state_processor));
		p_obsever->IsCollision("ITEMBROCK");
		break;
	}
	
	
	this->SetAccelaretor(this->GetGiaLevel());
}

void CPlayer::NOMAL::Update()
{
	if (GetTime() == 3){
		_owner->p_player->ChangeMoveType(PLAYER::PLAYERMOVETYPE::NOMAL);
		return;
	}
}

void CPlayer::ROTATION::Update()
{
	if (GetTime() == 3){
		_owner->p_player->ChangeMoveType(PLAYER::PLAYERMOVETYPE::ROTATION);
		return;
	}
}

CPlayer::IDOL::IDOL(CPlayerStateProcessor* owner) : _owner(owner)
{
	_owner->p_player->p_hitbox = new HitBox();
	_owner->p_player->ChildObj_AddListBegin((ChildObjRef)_owner->p_player->p_hitbox);

	_owner->p_player->p_hitbox->Settags("player");
	_owner->p_player->p_hitbox->transform.localposition.y += 0.1f;
}

void CPlayer::IDOL::Update()
{

}

CPlayer::DAMAGE::DAMAGE(CPlayerStateProcessor* owner) : _owner(owner)
{
	if (_owner->p_player->p_hitbox != nullptr) { _owner->p_player->p_hitbox->Remove(); };

	_owner->p_player->p_effekseer->PlayEffekseer(PLAYER::ITEM);
	_owner->p_player->p_obsever->IsCollision("DAMAGE");
}

void CPlayer::DAMAGE::Update()
{
	_owner->p_player->alpha   ^= 1;_owner->p_player->color_r  = 1;

	if (this->GetTime() >= 30)
	{
		_owner->p_player->alpha   = 1;_owner->p_player->color_r = 0;
		_owner->p_player->p_state_processor.ChangeState(new CPlayer::IDOL(&_owner->p_player->p_state_processor));
		return;
	}
}

CPlayer::RECOVERY::RECOVERY(CPlayerStateProcessor* owner) : _owner(owner)
{

	_owner->p_player->p_effekseer->PlayEffekseer(PLAYER::ITEM);
    _owner->p_player->p_obsever->IsCollision("RECOVERY");
}

void CPlayer::RECOVERY::Update()
{
	
	return;
}