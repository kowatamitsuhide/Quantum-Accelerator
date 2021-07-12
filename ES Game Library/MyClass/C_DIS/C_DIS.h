#pragma once
//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "../../ESGLib.h"
#include "../C_OBJECT/Object.h"

//------------------------------------------------------------------------------
//	この関数は２つの座標の距離を調べタグの中で最短の値を取得出来ます。
//------------------------------------------------------------------------------
class C_Distance : public Object
{
private:
	//自分自身を返す
	C_Distance* GetThisDis(){ return this; };

	static std::list<C_Distance*> c_dis_list;

	std::string tag;

	std::vector<C_Distance*> C_Distance::DistanceList(std::string _tag);
	std::vector<float>       C_Distance::IsOtherTagDistance(std::vector<C_Distance*> tag_c_dis);
public:

	C_Distance() {};

	virtual ~C_Distance() { IsRemove(); };

	void  Init();

	void  IsRemove();

	float GetTagDistance(std::string _tag);

	void IsTagSet(std::string _tag);

	bool TagSerch(std::string _tag);
};