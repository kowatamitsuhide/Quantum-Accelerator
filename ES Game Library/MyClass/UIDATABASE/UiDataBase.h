#pragma once
#include "../../ESGLib.h"
#include "../CSHAREDMETHOD/CSharedMethod.h"

class  IUiParametor;
struct UiParam;
class  UiData;

struct UiParam {
	int gage_size   = 100;
	int speed_meter = 1;
};

class IUiParametor
{
public:
	friend class UiData;

	IUiParametor() {};
	virtual ~IUiParametor() {};

	static IUiParametor& Instance() {
		static IUiParametor instance;
		return instance;
	};

	void CreateParametor(std::string name) { _ui_params.emplace(name, _ui_param); }
private:
	IUiParametor(const IUiParametor&)   = delete;
	void operator=(const IUiParametor&) = delete;

	std::map<std::string, UiParam> _ui_params;
	UiParam                        _ui_param;
};


class UiData : public CSharedMethod
{
public:
	UiData() {};
	virtual ~UiData() {};

	void SetGageParams(std::string name, int num) {
		if (IUiParametor::Instance()._ui_params.count(name) == 0)
			ASSERT("連想配列の存在しません。");

		IUiParametor::Instance()._ui_params[name].gage_size = clamp(num, 0, 100);

	}

	void SetSpeedMeterParams(std::string name, int num) {
		if (IUiParametor::Instance()._ui_params.count(name) == 0)
			ASSERT("連想配列の存在しません。");

		IUiParametor::Instance()._ui_params[name].speed_meter = clamp(IUiParametor::Instance()._ui_params[name].speed_meter + num, 1, 9);
	}

	int GetGageParams(std::string name)
	{
		if (IUiParametor::Instance()._ui_params.count(name) == 0)
			ASSERT("連想配列の存在しません。");

		return IUiParametor::Instance()._ui_params[name].gage_size;
	}

	int GetSpeedMeterParams(std::string name)
	{
		if (IUiParametor::Instance()._ui_params.count(name) == 0)
			ASSERT("連想配列の存在しません。");

		return IUiParametor::Instance()._ui_params[name].speed_meter;
	}
};
