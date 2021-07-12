#pragma once
#include "../../ESGLib.h"

class  IModelParametor;
struct ModelParam;
class  IModelData;

struct ModelParam {
	MODEL _model;
};

class IModelParametor
{
public:
	friend class IModelData;

	IModelParametor() {};
	virtual ~IModelParametor() {};

	static IModelParametor& Instance() {
		static IModelParametor instance;
		return instance;
	};

	void CreateParametor(std::string name) { _map_params.emplace(name, _map_param); }
private:
	IModelParametor(const IModelParametor&) = delete;
	void      operator=(const IModelParametor&) = delete;

	std::map<std::string, ModelParam> _map_params;
	ModelParam                        _map_param;
};


class IModelData
{
public:
	IModelData() {};
	virtual ~IModelData() {};

	void SetModelParams(std::string name, MODEL model) { 
		if (IModelParametor::Instance()._map_params.count(name) == 0)
			ASSERT("連想配列の存在しません。");

		IModelParametor::Instance()._map_params[name]._model = model;
	}
	MODEL GetModelParams(std::string name) 
	{ 
		if (IModelParametor::Instance()._map_params.count(name) == 0)
			ASSERT("連想配列の存在しません。");

		return IModelParametor::Instance()._map_params[name]._model;
	}
};
