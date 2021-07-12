#include "AccelaretorBase.h"
#include "MyClass/C_PLAYER/C_PLAYER.h"

float AccelaretorFront::_speed = 0.1f;

void AccelaretorFront::AccelaretorSpeed()
{
	this->_speed = this->_speed + this->_accelaretor;
	this->_speed = Math_Min(this->_speed, this->_max_speed);

	((CPlayer*)(this->gameObject))->MyCameraSetFieldOfViewY(0.4f);

	gameObject->transform.position.z = gameObject->transform.position.z + this->_speed;
}

void AccelaretorFront::DragSpeed()
{
	this->_speed = this->_speed * 0.99;
	this->_speed = Math_Max(this->_speed, _min_speed);

	gameObject->transform.position.z = gameObject->transform.position.z + this->_speed;
}

void AccelaretorFront::Init()
{
	_speed    += _accelaretor_parameter._start_velocity;
	_max_speed = _accelaretor_parameter._max_velocity;
	_min_speed = _accelaretor_parameter._min_velocity;
}

void AccelaretorFront::Update()
{
	Input.GetKeybordInput(Keys_Up) && _speed <= this->_max_speed ? AccelaretorSpeed() : DragSpeed();
}