#pragma once
#include "MyClass/C_OBJECT/Object.h"
#include "MyClass/C_STATE/C_STATE.h"
#include "AccelaretorBase.h"

class RotationMoveStateProcessor;
class RotationMove;

class RotationMoveStateProcessor : public  StateProcessor {
public:
	RotationMove* _rotation_move;
};

class RotationMove : public Object
{
private:
	float _tube_angle = 0.0f;

	RotationMoveStateProcessor _rotation_processor;

	AccelaretorFront* accelaretors;
public:

	RotationMove()  {};
	~RotationMove() {};

	virtual void RotationMove::Init()        override;
	virtual void RotationMove::Update()      override;

	void RotationMove::ProfarenceQuaternion();

	class IDOL : public State
	{
	private:
		RotationMoveStateProcessor* _owner;
	public:
		IDOL(RotationMoveStateProcessor* owner) : _owner(owner) {};
		virtual ~IDOL() {delete _owner;};
		virtual void Update() override;
	};

	class RUN : public State
	{
	private:
		RotationMoveStateProcessor* _owner;
	public:
		RUN(RotationMoveStateProcessor* owner) : _owner(owner) {}
		virtual ~RUN() {delete _owner;}
		virtual void Update() override;
	};
};

