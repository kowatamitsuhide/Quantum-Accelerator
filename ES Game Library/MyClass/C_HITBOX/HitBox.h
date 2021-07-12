#pragma once
#include "../../ESGLib.h"
#include "../C_OBJECT/Object.h"

class HitBox : public Object 
{
public:
	//デストラクタ
	HitBox::HitBox() {};

	virtual HitBox::~HitBox();

	virtual void HitBox::Init()   override;
	virtual void HitBox::Update() override { return; };
	virtual void HitBox::Draw3D() override;

	void HitBox::OnReMove();

	void HitBox::SetScale(Vector3 scale) { _model->SetScale(scale); };

	//自身を返す
	HitBox* HitBox::GetThisHitBox() { return this; };

	//衝突しているHitBoxのリストを取得
	std::list<HitBox*> HitBox::HitHitBoxlist();

	void    Settags(std::string tags);

	HitBox* HitBox::Get_Tag_HitBox(std::string tag);
	MODEL   HitBox::GetModel()   { return _model; };

	bool HitBox::IsHitObjects(std::string tags);

	bool _flag = false;

private:
	//全てのHitBoxを格納しておくリスト
	static std::list<HitBox*> _HitBox_list;

	//判定用のモデル
	MODEL _model = nullptr;
	std::string _tag;

	//衝突判定関数
	bool HitBox::IsHit(HitBox* other);

protected:
	
};