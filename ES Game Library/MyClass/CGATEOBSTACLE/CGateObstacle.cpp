#include "CGateObstacle.h"
#include "../INFORMATION/INFORMATION.h"

void CGateObstacle::Init()
{
	this->p_model.SetModel(_T("model3D//‰ü’ù”Å//GATE_Left.X"));

	p_hitbox = new HitBox();
	this->ChildObj_AddList((ChildObjRef)p_hitbox);

	p_hitbox->Settags("gate_L");
	p_hitbox->SetScale(Vector3(3.f, 0.5f, 0.5f));

	model_parameters.tags = 'Z';
	model_parameters.p_hitbox_position_revision = Vector3(-1.5f, 0.5f, 0.0f);

	this->attack_parameters._Type = ATTACK_TYPE::GAMEOVER;
}

void CGateObstacle::Update()
{
	gate_position.x = -(1.5f * 0.01f) * _iui_data->GetGageParams("ui");
}

void CGateObstacle::IsCollsion()
{
	
}

bool CGateObstacle::PModelParameter(std::vector<Vector3>::iterator& itr)
{
	this->transform.position.x += gate_position.x;
	this->OnCollsion();

	return false;
}