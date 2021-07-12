#pragma once
#include "../C_OBJECT/Object.h"
#include "../../ESGLib.h"

class ObstacleManager : public Object
{
	virtual void ObstacleManager::Init()        override;
	virtual void ObstacleManager::Update()      override { return; };
	virtual void ObstacleManager::Draw3D()      override { return; };

	virtual void ObstacleManager::DrawAlpha3D() override { return; };
	virtual void ObstacleManager::Draw2D()      override { return; };

};

