#pragma once
#include "../../ESGLib.h"
#include "../C_OBJECT/Object.h"

class EffekseerMng : public Object
{
public:
	EffekseerMng::EffekseerMng() {};
	EffekseerMng::~EffekseerMng() {};

	int       EffekseerMng::LoadEffekseer(TCHAR* filename);
	EFFEKSEER EffekseerMng::GetEffekseer(int _number);

	int EffekseerMng::PlayEffekseer(int _number);

	void EffekseerMng::PlayEffekseerAngle(int _number);

	virtual void Init()   override;
	virtual void Update() override;

	bool drection_flag = true;

private:

	std::vector<EFFEKSEER> effekseer;
	std::vector<int>       effekseer_id;
};
