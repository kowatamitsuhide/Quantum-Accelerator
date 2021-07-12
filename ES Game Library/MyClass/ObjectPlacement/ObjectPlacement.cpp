#include "ObjectPlacement.h"
#include"../C_UI/CUI.h"

PlacementManager::PlacementManager()
{

	FILE* fp = fopen("オブジェクト配置.csv", "r");

	char load_char[99999 + 1];

	while (fgets(load_char, sizeof load_char - 1, fp) != NULL)
	{
		std::string a = load_char;
		std::string b = ",";

		std::string c = b + a;

		mapdata.push_back(c);
	}

	for (int y = 0; y < mapdata.size(); y++)
	{
		for (int x = 0; x < mapdata[y].size(); x++)
		{
			if (mapdata[y][x] == ',' && mapdata[y][x + 1] == ',')
			{
				mapdata[y][x] = ' ';
			}

			if (mapdata[y][x] == ',')
			{
				mapdata[y].erase(mapdata[y].begin() + x);
			}
		}
		if (mapdata[y][mapdata[y].size()] == ',') { mapdata[y][mapdata[y].size()] = ' '; }
	}
	fclose(fp);

	_imap_data.reset(new IMapData);

	MapdataTagsPos();
}

void PlacementManager::Init()
{

}

void PlacementManager::Update()
{

}

void PlacementManager::Draw3D()
{

}

void PlacementManager::MapdataTagsPos()
{
	const float   sense    = 0.38f;
	const Vector3 lear_pos = Vector3(-1.33f, -0.3f, 50.0f);

	for (int z = 0; z < mapdata.size(); z++)
	{
		for (int x = 0; x < mapdata[z].size(); x++)
		{
			Vector3 position = Vector3((1 * sense) * x, (0 * sense), ((1 * sense) * z));
			char    map_tag  = mapdata[z][x];

			if (map_tag != '\n' && map_tag != ' ')
			{
				IMapParametor::Instance().CreateParametor(map_tag);

				switch (map_tag)
				{
				case 'G':
					_imap_data->SetPlayerPosition(map_tag,Vector3(0.0f,-0.3f,position.z + lear_pos.z));
					break;
				case 'Z':
					_imap_data->SetPlayerPosition(map_tag,Vector3(0.0f,-0.3f,position.z + lear_pos.z));
					break;
				default:
					_imap_data->SetPlayerPosition(map_tag, position + lear_pos);
					break;
				}
			}
		}
	}
	
}
