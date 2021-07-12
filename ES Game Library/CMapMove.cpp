#include "CMapMove.h"
#include "Myclass/C_PLAYER/C_PLAYER.h"
#include "C_Tonnel.h"
void CMapMove::Init()
{
	auto&& c_player = (new CPlayer(Vector3_Zero));
	this->ChildObj_AddList((ChildObjRef)c_player);

	auto&& c_tonnel = (new C_Tonnel());
	this->ChildObj_AddList((ChildObjRef)c_tonnel);
}

void CMapMove::Update()
{

}

void CMapMove::Draw3D()
{

}

void CMapMove::ObjectAdds(Object* object)
{
	if (this->gameObject == object) return;
	this->gameObject = object;
}
