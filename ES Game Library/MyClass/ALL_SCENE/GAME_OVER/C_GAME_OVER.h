#pragma once
#include "../SCENEMANAGER/BaseScreen.h"

class C_GAME_OVER : public BaseScene
{
public:

	C_GAME_OVER() {};
	virtual ~C_GAME_OVER() {};

	virtual void Initialize()  override;
	virtual void Update()      override;
	virtual void Draw3D()      override { return; };
	virtual void Draw2D()      override;
	virtual void DrawAlpha3D() override { return; };

private:
	SPRITE sprite;

	void Add_Sprite(LPCTSTR _sprite_name);
	std::vector<SPRITE> sprite_list_name;
};

