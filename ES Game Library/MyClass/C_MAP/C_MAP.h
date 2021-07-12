#pragma once

/**
 * @file   Result.h
 * @brief  背景のモデルをセットし背景を描画するクラス
 * @author Mitsuhide Kowata
 * @date 　2020/10/15
 */

#include "../C_OBJECT/Object.h"
#include "../../ESGLib.h"
#include "../CPLAYERDATA/CPlayerData.h"

class C_MAP : public Object
{
public:

	virtual void Init()        override;
	virtual void Update()      override;
	virtual void Draw3D()      override;

	virtual void DrawAlpha3D() override { return; }

private:

	void AddModelParametor(LPCTSTR _filename, int scene, Vector3 position);

	std::vector<MODEL> model;
	std::vector<std::vector<Vector3>> model_position;
	std::vector<int>                  model_scene;

	MEDIA bg;
	MUSIC bgm;
	const Vector3 road_init_pos   = Vector3(0.0f, -0.25f, 0.0f);
	const Vector3 bill_init_pos   = Vector3(0.0f,  -8.0f, 0.0f);
	const Vector3 pillar_init_pos = Vector3_Zero;

	//!プレイヤーのデータベース
	std::unique_ptr<IPlayerData>   _iplayer_data;

	/**
    * @enum Interval
    * モデルの描画間隔
    */
	enum Interval {
		//!道路の描画間隔
		ROAD_INTERVAL   = 17,
		//!柱の描画間隔
		PILLAR_INTERVAL = 23,
		//!建物の描画間隔
		BILL_INTERVAL   = 60
	};


	/**
　　* @enum Models
　　* モデルの個数や削除する座標の指定
　　*/
	enum Models {
		//!表示するモデルの個数
		MODEL_SIZE = 8,
		//!モデルを削除するポジション
		REMOVE_POS = 20
	};
protected:

};