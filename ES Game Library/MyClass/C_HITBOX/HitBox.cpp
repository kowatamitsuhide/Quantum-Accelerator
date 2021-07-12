#include "HitBox.h"

std::list<HitBox*> HitBox::_HitBox_list;

//デストラクタ
HitBox::~HitBox() 
{
	OnReMove();
}
void HitBox::Init() {
	//自分をリストに挿入
	_HitBox_list.push_back(this);

	//タグ設定
	_tag = "HitBox";

	SimpleShape   shape;
	shape.Type = Shape_Box;
	shape.Width = 1.0f;shape.Height = 1.0f;shape.Depth = 1.0f;
	_model = GraphicsDevice.CreateModelFromSimpleShape(shape);

	_model->SetScale(0.3f);
};

void HitBox::Draw3D() {
	if (_flag) return;
	_model->SetPosition(this->transform.position);
	//_model->Draw();
}

void HitBox::Settags(std::string tags){
	_tag = tags;
}

// 消去時に呼ばれる処理
void HitBox::OnReMove() {
	auto it = _HitBox_list.begin();
	while (it != _HitBox_list.end()) {
		if ((*it) != this) {
			it++;
		}
		else {
			it = _HitBox_list.erase(it);
			return;
		}
	}
}

bool HitBox::IsHit(HitBox* other) {
	OrientedBoundingBox model_obb1 = this->_model->GetOBB();
	OrientedBoundingBox model_obb2 = other->_model->GetOBB();
	return model_obb1.Intersects(model_obb2);
}

std::list<HitBox*> HitBox::HitHitBoxlist() {
	std::list<HitBox*>  result;
	for (auto&& h : _HitBox_list) {
		if (h->GetThisHitBox() == this) continue;
		if (h->IsHit(this)) result.push_back(h->GetThisHitBox());
	}
	return result;
};

HitBox* HitBox::Get_Tag_HitBox(std::string tag)
{
	HitBox* hitbox = nullptr;
	for (auto&& other_hitbox : _HitBox_list)
	{
		if (other_hitbox->_tag != tag) continue;
		if (this == other_hitbox->GetThisHitBox()) continue;

		hitbox = other_hitbox->GetThisHitBox();
	}

	return hitbox;
}

bool HitBox::IsHitObjects(std::string tags)
{
	bool result = false;
	std::list<HitBox*> HitList = HitHitBoxlist();
	for (auto&& other : HitList)
	{
		if (other->_tag == tags) 
		{
			result = true;
		}
	}
	return result;
}
