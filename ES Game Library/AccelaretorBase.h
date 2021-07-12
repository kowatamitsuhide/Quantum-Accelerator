#pragma once
#include "ESGLib.h"
#include "MyClass/C_OBJECT/Object.h"

enum ACCELARETOR_TYPE {NOMAL,ROW,MEDIUM,HARD,_END};

struct Accelaretor_Parameter {
public:
	//ó^Ç¶ÇÈÉ_ÉÅÅ[ÉWó 
	float _max_velocity;
	float _min_velocity;
	float _start_velocity;
};

class AccelaretorFront : public Object
{
private:
	static float _speed;
	float _accelaretor = 0.0030f;

	float _max_speed;
	float _min_speed;

	void AccelaretorFront::AccelaretorSpeed();
	void AccelaretorFront::DragSpeed();

	Accelaretor_Parameter _accelaretor_parameter;

public:

	void AccelaretorFront::SetAccelaretorParameter(Accelaretor_Parameter accelaretor_parameter) { _accelaretor_parameter = accelaretor_parameter; };
	void Init()   override;
	void Update() override;
};

