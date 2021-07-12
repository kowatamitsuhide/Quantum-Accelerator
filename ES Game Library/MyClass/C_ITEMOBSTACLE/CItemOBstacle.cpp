#include "CItemOBstacle.h"


void CItemObstacle::Init()
{
	this->p_model.SetModel(_T("‰ü’ù//obj_f.X"));
	this->p_model.SetScale(0.5f);

	p_hitbox = new HitBox();
	this->ChildObj_AddList((ChildObjRef)p_hitbox);

	p_hitbox->Settags("item");
	p_hitbox->transform.localposition.y += 0.5f;

	model_parameters.tags = 'I';
	model_parameters.p_hitbox_position_revision.y = 0.5f;
	model_parameters.p_model_position_revision.y  = 0.25f;

	this->attack_parameters._Type = ATTACK_TYPE::ITEM;
}

void CItemObstacle::Update()
{
	
}

void CItemObstacle::IsCollsion()
{

}

bool CItemObstacle::PModelParameter(std::vector<Vector3>::iterator& itr)
{
	if (this->OnCollsion()) { return true; }
	return false;
}


