#include "R_GATEOBSTATCLE.h"
#include"../C_UI/CUI.h"


void R_GATEOBSTATCLE::Init()
{
	this->p_model.SetModel(_T("model3D//‰ü’ù”Å//GATE_Right.X"));

	p_hitbox = new HitBox();
	this->ChildObj_AddList((ChildObjRef)p_hitbox);

	p_hitbox->Settags("gate_R");
	p_hitbox->SetScale(Vector3(3.f, 0.5f, 0.5f));

	model_parameters.tags = 'G';
	model_parameters.p_hitbox_position_revision = Vector3(1.5, 0.5f, 0.0f);

	this->attack_parameters._Type = ATTACK_TYPE::GAMEOVER;
}

void R_GATEOBSTATCLE::Update()
{
	gate_position.x = (1.5f * 0.01f) * _iui_data->GetGageParams("ui");
}

void R_GATEOBSTATCLE::IsCollsion()
{
	
}

bool R_GATEOBSTATCLE::PModelParameter(std::vector<Vector3>::iterator& itr)
{
	this->transform.position.x += gate_position.x;
	this->OnCollsion();

	return false;
}
