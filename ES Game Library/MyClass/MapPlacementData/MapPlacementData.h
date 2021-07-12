#pragma once
#include "../../ESGLib.h"

class  IMapParametor;
struct MapParam;
class  IMapData;

struct MapParam {
	std::vector<Vector3>  _position;
};

class IMapParametor
{
public:
	friend class IMapData;

	IMapParametor() {};
	virtual ~IMapParametor() {};

	static IMapParametor& Instance() {
		static IMapParametor instance;
		return instance;
	};

	void CreateParametor(char name) { _map_params.emplace(name, _map_param); }
	std::map<char, MapParam> _map_params;
private:
	IMapParametor(const IMapParametor&) = delete;
	void      operator=(const IMapParametor&) = delete;

	MapParam                 _map_param;
};


class IMapData
{
public:
	IMapData() {};
	virtual ~IMapData() {};

	void SetPlayerPosition(char name, Vector3 position)
	{
		if (IMapParametor::Instance()._map_params.count(name) == 0)
			ASSERT("連想配列の存在しません。");

		IMapParametor::Instance()._map_params[name]._position.push_back(position);
	}

	std::vector<Vector3>& GetPlayerPosition(char name)
	{
		if (IMapParametor::Instance()._map_params.count(name) == 0)
			ASSERT("連想配列の存在しません。");

		return IMapParametor::Instance()._map_params[name]._position;
	}

};