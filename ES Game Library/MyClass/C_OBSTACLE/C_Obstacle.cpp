#include "C_Obstacle.h"


void CObstacle::Init()
{
	this->p_model.SetModel(_T("model3D//‰ü’ù”Å_//timer.X"));

	p_hitbox = new HitBox();
	p_hitbox->Settags("hako_B");
	this->ChildObj_AddList((ChildObjRef)p_hitbox);

	model_parameters.tags = 'P';
	model_parameters.p_hitbox_position_revision.y = 0.5f;
	model_parameters.p_model_position_revision.y = 0.05f;

	this->attack_parameters._Type = ATTACK_TYPE::ITEMBROCK;
}

void CObstacle::Update()
{

}

void CObstacle::IsCollsion()
{

	return;
}

bool CObstacle::PModelParameter(std::vector<Vector3>::iterator& itr)
{
	this->OnCollsion();
	return false;
}