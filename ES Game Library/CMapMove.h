#pragma once
#include "ESGLib.h"
#include "MyClass//C_OBJECT/Object.h"

class CMapMove : public Object
{
public:
	virtual void CMapMove::Init()        override;
	virtual void CMapMove::Update()      override;
	virtual void CMapMove::Draw3D()      override;

	virtual void CMapMove::DrawAlpha3D() override { return; };
	virtual void CMapMove::Draw2D()      override { return; };

	void ObjectAdds(Object* object);

private:
};

