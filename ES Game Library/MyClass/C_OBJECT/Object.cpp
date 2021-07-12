#define _CRT_SECURE_NO_WARNINGS

#include "Object.h"

//---------------------------------------------
//◆定数指定
//---------------------------------------------
//
//----------------------------------------------
//◆Transform
//----------------------------------------------
    //更新
	void Transform::Update() {
		if (parent == nullptr) return;

		//初回時のみ
		if (backupposition == Vector3_Zero) backupposition = parent->position;
		if (backuprotation == Vector3_Zero) backuprotation = parent->rotation;
		if (backupscale == -0.0f) backupscale = parent->scale;

		     //ローカル座標を更新
		     localposition = Vector3_Add(localposition, Vector3_Add(position,-backupposition));
		     localrotation = Vector3_Add(localrotation, Vector3_Add(rotation, -backuprotation));
		     localscale    = localscale * MathHelper_Max(scale / backupscale,1.0f);

			//座標を更新
			position = Vector3_Add(localposition, parent->position);
			rotation = Vector3_Add(localrotation, parent->rotation);
			scale    = localscale * parent->scale;

			//バックアップを取る
			backupposition = position;
			backuprotation = rotation;
			backupscale    = MathHelper_Max(scale, 1.0f);
		}

//---------------------------------------------
//◆オブジェクト
//---------------------------------------------

//子オブジェクトリストに挿入
void Object::ChildObj_AddList(ChildObjRef& c) {
	//親として自分を指定
	c->gameObject = this;
	//親を元に座標更新
	c->transform.parent = &this->transform;
	c->transform.position = Vector3_Add(c->transform.position ,c->transform.parent->position);
	c->transform.rotation = Vector3_Add(c->transform.rotation, c->transform.parent->rotation);
	c->transform.scale = c->transform.scale / c->transform.parent->scale;
	c->transform.Update();
	//リストに挿入
	this->p_childObjects.push_back(c);	
	//初期化関数を呼ぶ
	c->Init();
}

//子オブジェクトリストに挿入
void Object::ChildObj_AddListBegin(ChildObjRef& c)
{
	//親として自分を指定
	c->gameObject = this;
	//親を元に座標更新
	c->transform.parent = &this->transform;
	c->transform.position = Vector3_Add(c->transform.position, c->transform.parent->position);
	c->transform.rotation = Vector3_Add(c->transform.rotation, c->transform.parent->rotation);
	c->transform.scale = c->transform.scale / c->transform.parent->scale;
	c->transform.Update();
	//リストに挿入
	this->p_childObjects.insert(p_childObjects.begin(), c);
	//初期化関数を呼ぶ
	c->Init();
}

//子オブジェクトの更新
void Object::ChildUpdate() {
   //消去フラグがTRUEなら消去
   auto it = p_childObjects.begin();
   while (it != p_childObjects.end()) {
	if (!(*it)->IsRemove()) {
	   it++;
	}
	else {
	   it = p_childObjects.erase(it);
	}
   }

	//Activeでない場合更新しない
	if (!_isActive) return;

	//Transform更新
	transform.Update();

	//Update呼び出し
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef& c) {if (c->GetActive()) c->Update(); });
		
	//子のUpdate呼び出し
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef& c) {c->ChildUpdate();});

	//消去フラグがTRUEなら消去
	auto end = std::remove_if(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef& c) {return c->IsRemove(); });
	p_childObjects.erase(end, p_childObjects.end());
}

//子の描画
void Object::ChildDraw2D() {
	//描画
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef & c) {c->Draw2D();});
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef & c) {c->ChildDraw2D();});
}
void Object::ChildDraw3D() {
	//描画
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef& c) {c->Draw3D();});
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef& c) {c->ChildDraw3D();});
}
void Object::ChildDrawAlpha3D() {
	//描画
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef & c) {c->DrawAlpha3D();});
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef & c) {c->ChildDrawAlpha3D();});
}

void Object::ChildDrawEnd()
{
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef& c) {c->DrawEnd(); });
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef& c) {c->ChildDrawEnd(); });
}

//消去
void Object::Remove() {
   this->_isRemove = true;
   for (auto&& i : p_childObjects) { i->Remove(); }
   this->OnRemove();
   this->transform.Remove();
}

//消去フラグを返す
bool Object::IsRemove() {
	return _isRemove;
}

//Activeを変更
void Object::SetActive(bool istrue) {
	//同値なら何もしない
	if (_isActive == istrue) return;
	_isActive = istrue;
	//std::for_each(ChildObj_list.begin(), ChildObj_list.end(), [istrue](ChildObjRef& c) {c->SetActive(istrue);});
}
//---------------------------------------------
//◆オブジェクトマネージャー
//---------------------------------------------
//初期化
void ObjectManager::Init() {}

//更新
void ObjectManager::Update() {
	_root.ChildUpdate();
}

//描画
void ObjectManager::Draw2D() {
	_root.ChildDraw2D();
}
void ObjectManager::Draw3D() {
	_root.ChildDraw3D();
}
void ObjectManager::DrawAlpha3D() {
	_root.ChildDrawAlpha3D();
}

void ObjectManager::DrawEnd(){
	_root.ChildDrawEnd();
}

//子オブジェクトリストに挿入
void ObjectManager::AddList(ChildObjRef& c) {
	_root.ChildObj_AddList((ChildObjRef)c);
}
void ObjectManager::AddListBegin(ChildObjRef& c) 
{
	_root.ChildObj_AddListBegin((ChildObjRef)c);
}