#pragma once
#include "../OBSTACLEBASE/ObstacleBase.h"

class R_GATEOBSTATCLE : public ObstacleBase
{
public:
	R_GATEOBSTATCLE() {};
	virtual ~R_GATEOBSTATCLE() {};

	virtual void Init()        override;
	virtual void Update()      override;

	virtual void IsCollsion()  override;
	virtual bool PModelParameter(std::vector<Vector3>::iterator& itr)  override;
private:

	Vector3 gate_position = Vector3(0.0f, 0.0f, 0.0f);

};