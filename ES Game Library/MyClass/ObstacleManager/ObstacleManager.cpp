#include "ObstacleManager.h"

#include "../C_OBSTACLE/C_Obstacle.h"
#include "../C_OBSTACLEL/CObstacleL.h"
#include "../C_OBSTACLER/CObstacleR.h"
#include "../CBROCKOBSTACLE/CBrockObstacle.h"
#include "../CGATEOBSTACLE/CGateObstacle.h"
#include "../C_GATEOBSTATCLE/R_GATEOBSTATCLE.h"
#include "../C_ITEMOBSTACLE/CItemOBstacle.h"

void ObstacleManager::Init()
{
	auto&& c_obstacle = new CObstacle();
	this->ChildObj_AddList((ChildObjRef)c_obstacle);

	auto&& c_obstacleL = new CObstacleL();
	this->ChildObj_AddList((ChildObjRef)c_obstacleL);

	auto&& c_obstacleR = new CObstacleR();
	this->ChildObj_AddList((ChildObjRef)c_obstacleR);

	auto&& c_itemobstacle = new CItemObstacle();
	this->ChildObj_AddList((ChildObjRef)c_itemobstacle);

	auto&& c_gateobstacle = new CGateObstacle();
	this->ChildObj_AddList((ChildObjRef)c_gateobstacle);

	auto&& c_gateobstatcle = new R_GATEOBSTATCLE();
	this->ChildObj_AddList((ChildObjRef)c_gateobstatcle);

	auto&& c_brockobstacle = new CBrockObstacle();
	this->ChildObj_AddList((ChildObjRef)c_brockobstacle);
}
