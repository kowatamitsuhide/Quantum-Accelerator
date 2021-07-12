#include "CObstacleR.h"

void CObstacleR::Init()
{
	this->p_model.SetModel(_T("model3D//‰ü’ù”Å_//MOVEBOX//hako_P.X"));

	p_hitbox = new HitBox();
	p_hitbox->Settags("moveboxL");
	p_hitbox->transform.localposition.y += 0.5f;

	this->ChildObj_AddList((ChildObjRef)p_hitbox);

	model_parameters.tags = 'R';
	model_parameters.p_hitbox_position_revision.y = 0.5f;
	model_parameters.p_model_position_revision.y  = 0.08f;
	
	this->attack_parameters._Type = ATTACK_TYPE::DAMEGE;
}

void CObstacleR::Update()
{

}

void CObstacleR::IsCollsion()
{

}

bool CObstacleR::PModelParameter(std::vector<Vector3>::iterator& itr)
{
	this->OnCollsion();

	if (this->p_distance <= 4.0f) { this->transform.position = *itr += Vector3(0.1f, 0.0f, 0.0f); };

	return false;
}