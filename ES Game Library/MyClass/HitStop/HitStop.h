
#pragma once
#include "../C_OBJECT/Object.h"

//ヒットストップ
class HitStop : public Object {
private:
   //ヒットストップ残り時間
   int _count = 0;
   //止める対象
   Object* p_taget;
public:
   //初期化
   void HitStop::Init();
   //更新
   void HitStop::Update();
   //ヒットストップ値設定
   void HitStop::SetStopCount(int damage);
   //ヒットストップ中か
   bool HitStop::IsStop();
   //対象指定
   void HitStop::SetTaget(Object* taget) 
   {
	p_taget = taget;
   };
};