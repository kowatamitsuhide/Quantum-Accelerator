#include "EffekseerMng.h"
#include "../ResouceManager/ResouceManager.h"


int EffekseerMng::LoadEffekseer(TCHAR* filename)
{
	EFFEKSEER _effekseer;
	_effekseer = ResouceManager::Instance().LordEffekseerFile(filename);

	effekseer.   push_back(_effekseer);
	effekseer_id.push_back(0);

	return /*effekseer.size() - 1*/ 0;
}

EFFEKSEER EffekseerMng::GetEffekseer(int _number)
{
    return effekseer[_number];
}

int EffekseerMng::PlayEffekseer(int _number)
{
	effekseer_id[_number] = effekseer[_number]->Play(this->gameObject->transform.position);

	//Vector3 front_vectol = gameObject->transform.position + Vector3_Forward;
	
	//effekseer[_number]->Stop(effekseer_id[_number]);

	return /*effekseer.size() - 1*/ 0;
}

void EffekseerMng::PlayEffekseerAngle(int _number)
{
	effekseer_id[_number] = effekseer[_number]->Play(this->gameObject->transform.position);
	Vector3 front_vectol = gameObject->transform.position + Vector3_Forward;

	Vector3 forward = Vector3_Forward;
	Vector3 effect_dir_ = Vector3_Zero;
	effect_dir_.y = MathHelper_ToRadians(-MathHelper_Atan2(forward.z, forward.x));
	effekseer[_number]->SetRotation(effekseer_id[_number], effect_dir_);
	effekseer[_number]->Stop(effekseer_id[_number]);
}

void EffekseerMng::Init()
{
	this->LoadEffekseer(_T("NitoriBox//ppppppp.efk"));
	this->LoadEffekseer(_T("NitoriBox//qqqqqqq.efk"));
	this->LoadEffekseer(_T("Hit_Effkt/Recovery.efk"));
}

void EffekseerMng::Update()
{
	for (int effekseer_idr = 0; effekseer_idr < effekseer_id.size(); effekseer_idr++)
	{
		effekseer[effekseer_idr]->SetPosition(effekseer_id[effekseer_idr], this->gameObject->transform.position + Vector3(0.0f, 0.0f, 0.5f));
		effekseer[effekseer_idr]->SetScale(effekseer_id[effekseer_idr], this->transform.scale);
	}
}

