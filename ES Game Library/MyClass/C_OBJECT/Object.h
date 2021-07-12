#pragma once

#include "../../ESGLib.h"
#include <algorithm>
#include "../ResouceManager/ResouceManager.h"
#include "../C_INPUT/Input.h"

class Transform;
class Object;
class ObjectManager;

//----------------------------------------------
//◆Transform
//----------------------------------------------
class Transform {
public:
	//座標
      Vector3 position = Vector3_Zero;
	Vector3 localposition= Vector3_Zero;
	
	//回転
	Vector3 rotation= Vector3_Zero;;
	Vector3  localrotation= Vector3_Zero;;

	Quaternion direction = Vector4(0.0f, 1.0f, 0.0f, 0.0f);

	//スケール
	float scale      = 1.f;
	float localscale = 1.f;

	//Transformの親
	Transform * parent = NULL;

	//更新
	void Transform::Update();

	//使用されていないか
	bool Transform::IsRemove() {
	   return _isremove;
	}
	void Transform::Remove() {
	   _isremove = true;
	}

private:
	//前フレームのバックアップ
	Vector3 backupposition = Vector3_Zero;
	Vector3 backuprotation = Vector3_Zero;
	float backupscale = 0.0f;

	//使用されていないか
	bool _isremove = false;
};

//---------------------------------------------
//◆オブジェクト
//---------------------------------------------
typedef std::shared_ptr<Object> ChildObjRef;
class Object {
protected:
   //リスト
   std::list<ChildObjRef> p_childObjects;

private:
   //消去フラグ
   //falseで更新を行わない
   bool _isActive = true;
   	
   bool _isRemove = false;
public:
	//親オブジェクト
	Object* gameObject = nullptr;

	Object* m_gameObject = nullptr;

	//座標
	Transform transform;
	//タグ
	std::string tag = "Default";

	//コンストラクタ
	Object() {
		m_gameObject = this;
	};

	//デストラクタ
	virtual ~Object() { this->Remove(); };

	//初期化
	virtual void Init() {};

	//更新
	virtual void Update() {};

	//子オブジェクトリストに挿入
	void ChildObj_AddList(ChildObjRef& c);
	void ChildObj_AddListBegin(ChildObjRef& c);

	virtual void ChildUpdate();

	//描画
	virtual void Draw2D() {};
	virtual void Draw3D() {};
	virtual void DrawAlpha3D() {};
	virtual void DrawEnd() {};

	
	//子の描画
	virtual void ChildDraw2D();
	virtual void ChildDraw3D();
	virtual void ChildDrawAlpha3D();
	virtual void ChildDrawEnd();

	//消去
	virtual void Remove();

	//消去タグ
	virtual void IsRemove_flag(bool _flag) { _isRemove = _flag; };

	//消去の際に呼ばれる処理
	virtual void OnRemove() {};

	//消去フラグを返す
	bool IsRemove();

	//子の数を返す
	int ChildListSize() { return p_childObjects.size(); };

	//Activeを変更
	void SetActive(bool i);
	bool GetActive() {
	   return _isActive;
	};
};

//---------------------------------------------
//◆オブジェクトマネージャー
//---------------------------------------------
class ObjectManager {
private:
	//ルートオブジェクト(全オブジェクトの親となる)
public:
	Object _root;
	//コンストラクタ
     ObjectManager() {};

   //デストラクタ
   virtual ~ObjectManager() {};

    //初期化
	void Init();

	//更新
	void Update();

	//描画
	virtual void Draw2D();
	virtual void Draw3D();
	virtual void DrawAlpha3D();

	virtual void DrawEnd();

	//子オブジェクトリストに挿入
	void AddList(ChildObjRef& c);
	void AddListBegin(ChildObjRef& c);
};