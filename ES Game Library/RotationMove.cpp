#include "RotationMove.h"
#include "MyClass/C_PLAYER/C_PLAYER.h"

void RotationMove::Init()
{
	_rotation_processor._rotation_move = this;
	_rotation_processor.ChangeState(new RotationMove::IDOL(&_rotation_processor));

	accelaretors = (new AccelaretorFront);
	this->ChildObj_AddList((ChildObjRef)accelaretors);

	this->m_gameObject = this;

	accelaretors->gameObject = gameObject;

}

void RotationMove::Update()
{
	this->_rotation_processor.Update();

	if (_tube_angle >= 360 || _tube_angle <= -360) { _tube_angle = 0.0f; }

	ProfarenceQuaternion();
}

void RotationMove::ProfarenceQuaternion()
{
	auto position = Vector3(0.0f, 1.0f, 0.0f);
	position.z = this->gameObject->transform.position.z;
	float tube_radius = 1.0f;

	Matrix matWorld = Matrix_Identity();
	matWorld *= Matrix_CreateRotationY(180.0f);
	matWorld *= Matrix_CreateTranslation(Vector3(0, -tube_radius, 0));
	matWorld *= Matrix_CreateRotationZ(_tube_angle);
	matWorld *= Matrix_CreateTranslation(position);

	this->gameObject->transform.direction = Quaternion_CreateFromRotationMatrix(matWorld);

	this->gameObject->transform.position = Vector3(matWorld._41, matWorld._42, matWorld._43);
}

void RotationMove::IDOL::Update()
{
	_owner->_rotation_move->_tube_angle = _owner->_rotation_move->_tube_angle * 0.985f;

	if (Input.GetArrowkeyVector().x != Vector3_Zero.x)
	{
		_owner->_rotation_move->_rotation_processor.ChangeState(new RotationMove::RUN(&_owner->_rotation_move->_rotation_processor));
		return;
	}
}

void RotationMove::RUN::Update()
{
	if (Input.GetArrowkeyVector().x == Vector3_Left.x)  { _owner->_rotation_move->_tube_angle -= 2.0f; }
	else
	if (Input.GetArrowkeyVector().x == Vector3_Right.x) { _owner->_rotation_move->_tube_angle += 2.0f; }

	if (Input.GetArrowkeyVector().x == Vector3_Zero.x)  {
		_owner->_rotation_move->_rotation_processor.ChangeState(new RotationMove::IDOL(&_owner->_rotation_move->_rotation_processor));
		return;
	}
}
