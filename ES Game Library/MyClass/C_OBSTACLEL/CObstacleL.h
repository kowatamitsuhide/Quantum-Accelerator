#pragma once
#include "../OBSTACLEBASE/ObstacleBase.h"

class CObstacleL : public ObstacleBase
{
public:
	CObstacleL() {};
	virtual ~CObstacleL() {};

	virtual void Init()        override;
	virtual void Update()      override;

	virtual void IsCollsion()  override;
	virtual bool PModelParameter(std::vector<Vector3>::iterator& itr)  override;

private:

};

