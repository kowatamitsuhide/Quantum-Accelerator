#include "CObstacleL.h"

void CObstacleL::Init()
{
	this->p_model.SetModel(_T("model3D//‰ü’ù”Å_//MOVEBOX//hako_P.X"));
	this->p_model.SetRotation(Vector3(0.0f, 0.0f, 180.0f));

	this->p_hitbox = new HitBox();
	this->p_hitbox->Settags("moveboxL");
	this->p_hitbox->transform.localposition.y -= 1.0f;

	this->ChildObj_AddList((ChildObjRef)p_hitbox);

	model_parameters.tags = 'L';
	model_parameters.p_hitbox_position_revision.y = 0.5f;
	model_parameters.p_model_position_revision.y = 0.85f;

	this->attack_parameters._Type = ATTACK_TYPE::DAMEGE;

}

void CObstacleL::Update()
{



}

void CObstacleL::IsCollsion()
{

}

bool CObstacleL::PModelParameter(std::vector<Vector3>::iterator& itr)
{
	this->OnCollsion();

	if (this->p_distance <= 4.0f) { this->transform.position = *itr += Vector3(-0.1f, 0.0f, 0.0f); };

	return false;
}
