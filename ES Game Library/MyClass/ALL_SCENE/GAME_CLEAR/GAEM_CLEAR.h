#pragma once
#include "../SCENEMANAGER/BaseScreen.h"

class GAEM_CLEAR : public BaseScene
{
public:
	GAEM_CLEAR() {};
	virtual ~GAEM_CLEAR() {};

	virtual void Initialize();
	virtual void Update();
	virtual void Draw3D() {};
	virtual void Draw2D();
	virtual void DrawAlpha3D() {};

private:
	SPRITE sprite;

	void Add_Sprite(LPCTSTR _sprite_name);
	std::vector<SPRITE> sprite_list_name;
};

