#pragma once

#include "../C_HITBOX/HitBox.h"
#include "../CSHAREDMETHOD/CSharedMethod.h"
#include "../OBSEVER/OBSEVER.h"

class CSharedMethod
{
public:
	//ラップアラウンド
	int         wrap(int x, int low, int high);
	//クランプ
	double      clamp(double x, double low, double high);

	//フレーム経過時間を伝える
	bool     FrameTimeObsever(int _index);

	int a = 5;

private:

	int _time;
};
