#pragma once
#include "../C_OBJECT/Object.h"
#include "../C_STATE/C_STATE.h"

class VelocityStateProcessor;
class Velocity;

class VelocityStateProcessor : public  StateProcessor {
public:
	Velocity* p_velosity;
};

class Velocity : public Object
{
public:
	static void CALLBACK timer_handle(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

	VelocityStateProcessor p_velocity_processor;

	//falseÇ≈å∏êäÇêÿÇÈ
	bool  _speed_attenuation_flag = true;

	static float _speed;

	const float _speed_drag = 0.98f;
	const float _max_speed  = 0;

	Velocity::Velocity();
	Velocity::~Velocity() {};

	void AxisDirection(Vector3 angle) { _axis_direction = angle; };

	virtual void Velocity::Init()   override { return; };
	virtual void Velocity::Update() override;

	bool Velocity::ZeroVelocity() 
	{
		return _speed == 0.0f;
	};

	static void GetTimerMethod();

	void SpeedAttenuationFlag(bool flag) { _speed_attenuation_flag = flag; };

	class IDOL : public State
	{
	private:
		VelocityStateProcessor* _owner;
	public:
		IDOL(VelocityStateProcessor* owner) : _owner(owner) {};
		virtual ~IDOL() {};

		virtual void Update() override;
	};

	class MOVE : public State
	{
	private:
		VelocityStateProcessor* _owner;
		MMRESULT uTimerID;
	public:
		MOVE(VelocityStateProcessor* owner) : _owner(owner) {}
		virtual ~MOVE();

		virtual void Update() override;
	};


private:

	Vector3 _axis_direction = Vector3(0.0f, 0.0f, 0.0f);

};