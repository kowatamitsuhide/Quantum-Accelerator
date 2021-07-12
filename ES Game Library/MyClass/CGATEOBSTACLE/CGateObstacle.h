#pragma once
#include "../OBSTACLEBASE/ObstacleBase.h"

class CGateObstacle : public ObstacleBase
{
public:
	CGateObstacle() {};
	virtual ~CGateObstacle() {};

	virtual void Init()        override;
	virtual void Update()      override;
	
	virtual void IsCollsion()  override;
	virtual bool PModelParameter(std::vector<Vector3>::iterator& itr)  override;

private:

	Vector3 gate_position = Vector3(0.0f, 0.0f, 0.0f);


};


