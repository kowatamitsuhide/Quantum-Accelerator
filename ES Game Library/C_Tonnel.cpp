#include "C_Tonnel.h"
#include "CMapMove.h"

void C_Tonnel::Init()
{
	p_model.SetModel(_T("model3D//‰ü’ù”Å_//Tunnel.X"));
	p_model.SetScale(0.25f);

	_imap_data.reset(new IMapData);
	_iplayer_data.reset(new IPlayerData);
}

void C_Tonnel::Update()
{
	if (p_model.GetModel()->IntersectRay(_iplayer_data->GetPlayerPosition("player"), Vector3_Down, nullptr, nullptr)){
		((CMapMove*)(gameObject))->ObjectAdds(this); 
	}
	else {
		((CMapMove*)(gameObject))->ObjectAdds(nullptr);
	}
}

void C_Tonnel::Draw3D()
{
	auto& itr = this->_imap_data->GetPlayerPosition('O');

	Vector3 player_pos = this->gameObject->transform.position;

	auto& obstacle_it   = itr.begin();
	while (obstacle_it != itr.end())
	{
		this->transform.position = *obstacle_it;
		float distance = this->transform.position.z - player_pos.z;

		if (distance <= 90)
		{
			if (distance <= -5.0f) { obstacle_it = itr.erase(obstacle_it); continue; };

			this->p_model.SetPosition(this->transform.position);
			this->p_model.Draw();
		}
		obstacle_it++;
	}

}
