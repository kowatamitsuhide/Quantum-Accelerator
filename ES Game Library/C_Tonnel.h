#pragma once
#include "ESGLib.h"
#include "MyClass/C_OBJECT/Object.h"
#include "MyClass/CCHARACTER/Character.h"
#include "MyClass/MapPlacementData/MapPlacementData.h"
#include "MyClass/CPLAYERDATA/CPlayerData.h"

class C_Tonnel : public Object
{
private:
	Model p_model;

	std::unique_ptr<IMapData>        _imap_data;
	std::unique_ptr<IPlayerData>     _iplayer_data;

public:
	virtual void C_Tonnel::Init()        override;
	virtual void C_Tonnel::Update()      override;
	virtual void C_Tonnel::Draw3D()      override;

	virtual void C_Tonnel::DrawAlpha3D() override { return; };
	virtual void C_Tonnel::Draw2D()      override { return; };

};

