#pragma once
#include "../../ESGLib.h"
#include "../../EnumManager.h"

// 衝突判定 観測者 インターフェース（ 観測 者 を 抽象化） 
class OBSERVERLISTENER
{
public:
	// 仮想 デストラクタ
	virtual ~OBSERVERLISTENER() {}
	// 衝突判定した
	virtual void OnCollision(std::string collsion_tag) {};
};

// 衝突判定 クラス（ 観測 者 に 通知 する 役）
class OBSERVER
{
public:
	// 観測者の登録 
	void addListener   (OBSERVERLISTENER* listener);
	void removeListener(OBSERVERLISTENER* listener);

	// 衝突判定した
	void IsCollision(std::string collsion_tag);

private:
	// 観測者に通知 

	static std::list<OBSERVERLISTENER*> listeners_;
};