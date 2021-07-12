#include "CBrockObstacle.h"

#include "../C_CAMERA/C_CAMERA.h"
#include "../../EnumManager.h"

void CBrockObstacle::Init()
{
	this->p_model.SetModel(_T("model3D//‰ü’ù”Å_//hako_P.X"));

	p_hitbox = new HitBox();
	p_hitbox->Settags("hako_P");
	this->ChildObj_AddList((ChildObjRef)p_hitbox);

	model_parameters.tags = 'B';
	model_parameters.p_hitbox_position_revision.y = 0.5f;
	model_parameters.p_model_position_revision.y  = 0.05f;

	this->attack_parameters._Type = ATTACK_TYPE::DAMEGE;

	return;
}

void CBrockObstacle::Update()
{

	return;
}

void CBrockObstacle::IsCollsion()
{

	return;
}

bool CBrockObstacle::PModelParameter(std::vector<Vector3>::iterator& itr)
{
	this->OnCollsion();
	return false;
}
