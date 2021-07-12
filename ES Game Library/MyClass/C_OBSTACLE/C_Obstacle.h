#pragma once
#include "../OBSTACLEBASE/ObstacleBase.h"

class CObstacle : public ObstacleBase
{
public:
	CObstacle() {};
	virtual ~CObstacle() {};

	virtual void Init()        override ;
	virtual void Update()      override ;

	bool CObstacle::PModelParameter(std::vector<Vector3>::iterator& itr) override;
	void CObstacle::IsCollsion() override;

private:


protected:

};