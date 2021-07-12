#include "C_MAP.h"

/**
 * @fn 　　背景モデルの初期位置
 * @brief　AddParametor関数で背景モデルの初期座標の設定
 * @return なし
 */
void C_MAP::Init()
{
	AddModelParametor(_T("model3D//改訂版//road_8.X"),       ROAD_INTERVAL, road_init_pos);
	AddModelParametor(_T("model3D//柱//kari.X"),           PILLAR_INTERVAL, pillar_init_pos);
	AddModelParametor(_T("model3D//bill_side//pro_set.X"),   BILL_INTERVAL, bill_init_pos);

	_iplayer_data.reset(new IPlayerData);
};

void C_MAP:: Update()
{
	//!プレイヤーの情報取得
	Vector3 player_position = _iplayer_data->GetPlayerPosition("player");

	for (int y = 0; y < model_position.size(); ++y) 
	{
		Vector3 position = *model_position[y].begin();
		int remove_position = REMOVE_POS;

		//!プレイヤーのZ座標より小さくなった場合、
		//!配列の一番前の場所を削除し、配列の一番後ろに追加する。
		if (position.z + remove_position <= player_position.z)
		{
			model_position[y].erase(model_position[y].begin());
			model_position[y].push_back(Vector3(position.x, position.y, (model_position[y].back().z + model_scene[y])));
		}
	}

	return;
};

void C_MAP::Draw3D()
{
	for (int y = 0; y < model_position.size(); ++y) 
	{
		for (int x = 0; x < model_position[y].size(); ++x)
		{
			model[y]->SetPosition(model_position[y][x]);
			model[y]->Draw();
		}
	}

	return;
};

/**
 * @fn    背景モデルの初期座標計算
 * @brief
 * @param (LPCTSTR _filename) 背景モデル名
 * @param (int scene)　　　　 モデルの描画する間隔
 * @param (Vector3 position)　モデルの一番最初の要素の初期座標
 * @return なし
 * @detail 
 */
void C_MAP::AddModelParametor(LPCTSTR _filename, int scene, Vector3 position)
{
	Material mtrl;
	mtrl.Emissive = Color(Vector3_One);

	model.push_back(GraphicsDevice.CreateModelFromFile(_filename)); //!モデルの作成
	model[model.size() - 1]->SetScale(transform.scale);             //!スケールの設定
	model[model.size() - 1]->SetMaterial(mtrl);                     //!マテリアルの設定
	model_scene.push_back(scene);                                   //!モデル同士の間隔の設定
	model_position.resize(model.size());                            //!モデル情報の配列の確保
	
	int model_size = MODEL_SIZE;

	//!モデルの初期座標を設定する
	for (int i = 0; i < model_size; i++)
	{
		model_position[model.size() - 1].push_back(position + Vector3(0.0f,0.0f,-5 + (i * scene)));
	}
}