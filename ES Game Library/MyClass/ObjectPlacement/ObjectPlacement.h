#pragma once
#include "../../ESGLib.h"
#include "../C_OBJECT/Object.h"
#include "../MapPlacementData/MapPlacementData.h"

class PlacementManager : public Object
{
public:

	PlacementManager();
   ~PlacementManager() {};

	virtual void Init()        override;
	virtual void Update()      override;
	virtual void Draw3D()      override;

	virtual void DrawAlpha3D() override { return; };
	virtual void Draw2D()      override { return; };

private:

	std::vector<cstring>  mapdata;

	void MapdataTagsPos();

	//プレイヤーのデータベース
	std::unique_ptr<IMapData>   _imap_data;
protected:
	
};