#include "Velocity.h"

float Velocity::_speed = 0.0f;

Velocity::Velocity()
{
	p_velocity_processor.p_velosity = this;
	p_velocity_processor.ChangeState(new Velocity::IDOL(&p_velocity_processor));
}

void Velocity::Update()
{
	gameObject->transform.position.z += 0.3f;

	this->p_velocity_processor.Update();
}

void Velocity::GetTimerMethod()
{
	_speed += 0.0025f;
}

void Velocity::IDOL::Update()
{
	if (this->_owner->p_velosity->_speed_attenuation_flag)
	{
		if (!this->_owner->p_velosity->ZeroVelocity())
		{	
			//速度減数
			this->_owner->p_velosity->_speed *= this->_owner->p_velosity->_speed_drag;
			//親の座標に加算する。
			this->_owner->p_velosity->gameObject->transform.position.x += this->_owner->p_velosity->_speed;
		}
	}

	if (this->_owner->p_velosity->_axis_direction.x != 0.0f)
	{
		_owner->p_velosity->p_velocity_processor.ChangeState(new Velocity::MOVE(&_owner->p_velosity->p_velocity_processor));
	}
}

void Velocity::MOVE::Update()
{
	uTimerID = timeSetEvent(60 * 1000, 1, (LPTIMECALLBACK)Velocity::timer_handle, (DWORD)this->_owner, TIME_PERIODIC);

	if ((float)this->_owner->p_velosity->_axis_direction.x == 0.0f)
	{
		_owner->p_velosity->p_velocity_processor.ChangeState(new Velocity::IDOL(&_owner->p_velosity->p_velocity_processor));
		return;
	}

	this->_owner->p_velosity->gameObject->transform.position.x += this->_owner->p_velosity->_axis_direction.x * (this->_owner->p_velosity->_speed);
}

Velocity::MOVE::~MOVE()
{
	timeKillEvent(uTimerID);
	this->_owner->p_velosity->_speed = 0.0f;
}

void CALLBACK Velocity::timer_handle(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	Velocity* velocity = (Velocity*)dwUser;
	velocity->GetTimerMethod();
}
