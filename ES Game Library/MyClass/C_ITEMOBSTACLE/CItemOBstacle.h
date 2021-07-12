#include "../OBSTACLEBASE/ObstacleBase.h"
#include "../OBSEVER/OBSEVER.h"

class CItemObstacle : public ObstacleBase
{
public:
	CItemObstacle() {};
	virtual ~CItemObstacle() {};

	virtual void Init()        override;
	virtual void Update()      override;

	virtual void IsCollsion()  override;

	virtual bool PModelParameter(std::vector<Vector3>::iterator& itr)  override;

private:

};