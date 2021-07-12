#pragma once
#include "../../ESGLib.h"

class  IPlayerParametor;
struct PlayerParam;
class  IPlayerData;

struct PlayerParam {
	Vector3      _player_position;

};

class IPlayerParametor
{
public:
	friend class IPlayerData;

	IPlayerParametor() {};
	virtual ~IPlayerParametor() {};

	static IPlayerParametor& Instance() {
		static IPlayerParametor instance;
		return instance;
	};

	void CreateParametor(std::string name) { _player_params.emplace(name, _player_param); }
private:
	IPlayerParametor   (const IPlayerParametor&) = delete;
	void      operator=(const IPlayerParametor&) = delete;

	std::map<std::string, PlayerParam> _player_params;
	PlayerParam                        _player_param;
};  


class IPlayerData
{
public:
	IPlayerData() {};
	virtual ~IPlayerData() {};

	void SetPlayerPosition(std::string name, Vector3 position)
	{
		if (IPlayerParametor::Instance()._player_params.count(name) == 0)
			ASSERT("連想配列の存在しません。");

		IPlayerParametor::Instance()._player_params[name]._player_position = position;
	}

	Vector3 GetPlayerPosition(std::string name) 
	{ 
		if (IPlayerParametor::Instance()._player_params.count(name) == 0)
			ASSERT("連想配列の存在しません。");

		return IPlayerParametor::Instance()._player_params[name]._player_position;
	}

};