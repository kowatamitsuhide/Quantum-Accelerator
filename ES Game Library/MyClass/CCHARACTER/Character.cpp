#include "Character.h"

/**
 * @file   Character.cpp
 * @brief  キャラクタ生成クラスソースファイル
 * @author 中島颯一朗
 * @date   2020/10/1
 */

 /**
  * @brief 設定(色の設定)
  * @param[in] (color)色の設定
  * @return    (mtrl) 設定した色
  */
Material ModelBase::SetMaterial(Color color)
{
	Material mtrl;

	ASSERT(color <= Color(1.0f, 1.0f, 1.0f) && "色は1.0f未満");

	mtrl.Diffuse  = color;
	mtrl.Ambient  = color;
	mtrl.Specular = color;
	mtrl.Emissive = color;
	mtrl.Power = 1.0f;

	return mtrl;
}

/**
 * @brief モデル設定(アニメーションモデルの読み込み、マテリアルの設定)
 * @param[in] (model_filename) アニメーションモデルのファイルネーム
 * @return    (なし)
 */
void AnimationModel::SetModel(LPCTSTR model_filename)
{
	_animation_model = GraphicsDevice.CreateAnimationModelFromFile(model_filename);
	_animation_model->SetMaterial(SetMaterial(Color(1.0f, 1.0f, 1.0f)));

	ASSERT(_animation_model != nullptr && "アニメーションモデルが入っていません。");
}

/**
 * @brief シェーダーの設定(シェーダーの読み込み)
 * @param[in] (model_filename)モデルのテクスチャ
 * @return    (なし)
 */
void AnimationModel::SetShader(LPCTSTR model_filename)
{
	_shader.reset(new CShaderAnimation);

	SPRITE sprite = GraphicsDevice.CreateSpriteFromFile(model_filename);
	IDirect3DTexture9* texture = *sprite;

	ASSERT(texture != nullptr && "画像が見つからない!");

	_shader->ShaderInitialize(model_filename, _T("FX/Light.hlsl"));
}

/**
 * @brief 再生速度(アニメーションモデルの再生フレームの設定)
 * @param[in] (animation_speed)　再生速度	
 * @return    (なし)
 */
void AnimationModel::SetAdvanceTime(int generating_time, int animation_speed)
{
	_generating_time = generating_time;
	_animation_speed = animation_speed;
}


/**
 * @brief 描画(シェーダーを適用した状態の描画)
 * @param[in] (alpha)　不透明度
 * @return    (なし)
 */
void AnimationModel::DrawShader(float alpha)
{
	//アニメーションモデルかモデルか
	_shader->IsModelPass(_animation_model);

	float _alpha = alpha;

	EFFECT shader = _shader->ShaderDraw(_alpha, _animation_model->GetPosition());

	//アニメーションモデル再生
	_animation_model->AdvanceTime((_generating_time / _animation_speed));
	_animation_model->Draw(shader);
}

/**
 * @brief 描画(普通の描画)
 * @return    (なし)
 */
void AnimationModel::Draw()
{
	_animation_model->AdvanceTime((_generating_time / _animation_speed));
	_animation_model->Draw();
}

/**
 * @brief 描画(影を適用した状態の描画)
 * @param[in] (なし)
 * @return    (なし)
 */
void AnimationModel::DrawShadow()
{
	GraphicsDevice.BeginShadowRendering();
	Matrix mat;

	mat = Create_Shadow(Light_Directional, Vector3_Zero, GetPosition(), Vector3(0.0f, 0.1f, 0.0f), Vector3_Up);

	_animation_model->DrawShadow(mat, /*影の濃度*/0.75f);

	GraphicsDevice.EndShadowRendering();

	_animation_model->AdvanceTime((_generating_time / _animation_speed));
	_animation_model->Draw();
}


/**
 * @brief　切り替え(アニメーション切り替え)
 * @param[in] (new_state)　再生したいアニメーションのトラック
 * @return    (なし)
 */
void AnimationModel::SetPlayerState(int new_state)
{
	if (_player_state == new_state) { return; }
	else {
		_animation_model->SetTrackEnable(_player_state, FALSE);
		_animation_model->SetTrackEnable(new_state, TRUE);
		_animation_model->SetTrackPosition(new_state, 0);
		_player_state = new_state;
	}
}

/**
 * @brief 影の生成
 * @param[in] (light_type)　ライトのタイプ
 * @param[in] (light)     　ライトの情報
 * @param[in] (pos)     　  プレイヤーの座標
 * @param[in] (shadowoffset)影の濃度
 * @return    (maT)         設定した影の情報
 */
inline Matrix AnimationModel::Create_Shadow(const D3DLIGHTTYPE light_type, const Vector3& light, const Vector3& pos, const Vector3& shadow_offset, const Vector3& normal)
{
	D3DXVECTOR4   Light;
	Light = D3DXVECTOR4(light + Vector3(0, 1500000, 150000) - pos, 0.0f);
	::D3DXVec4Normalize(&Light, &Light);

	D3DXPLANE     Plane;
	::D3DXPlaneFromPointNormal(&Plane, &(pos + shadow_offset), &normal);

	D3DXMATRIX   matT;
	::D3DXMatrixShadow(&matT, &Light, &Plane);

	return matT;
}

Model::Model()
{
	_iplayer_data.reset(new IPlayerData);
}

/**
 * @brief　モデルの設定(モデルの読み込み)
 * @param[in] (model_filename)　モデルのファイルネーム
 * @return    (なし)
 */
void Model::SetModel(LPCTSTR model_filename)
{
	_model = GraphicsDevice.CreateModelFromFile(model_filename);
	_model->SetMaterial(SetMaterial(Color(1.0f, 1.0f, 1.0f)));

	ASSERT(_model != nullptr && "モデルが見つかりません。");
}

/**
 * @brief　シェーダーの設定(シェーダーにテクスチャの読み込み)
 * @param[in] (model_filename)　モデルのテクスチャ
 * @return    (なし)
 */
void Model::SetShader(LPCTSTR model_filename)
{
	_shader.reset(new CShaderModel());

	_shader->ShaderInitialize(model_filename, _T("FX/Light.hlsl"));
}

/**
 * @brief　描画(モデルの描画)
 * @param[in] (なし)
 * @return    (なし)
 */
void Model::Draw()
{
	_model->Draw();
}
/// <brief>シェーダーを適用版の描画</brief>
/// <param  alpha>モデルの不透明度</param>
/// <returns>備考</returns>
void Model::DrawShader(float alpha)
{
	ASSERT(alpha >= 0.0f && alpha <= 1.0f && "alpha値は1未満");

	_shader->IsModelPass(_model);

	EFFECT shader = _shader->ShaderDraw(alpha, _iplayer_data->GetPlayerPosition("player"));

	_model->Draw(shader);
}

/**
 * @brief　スポットライトの範囲
 * @param[in] (なし)
 * @return    (なし)
 */
void Model::Attenuation(float attenuation)
{
	ASSERT(attenuation <= 1.0f && "ライトの光源は1.0未満の値にしてください");

	_shader->SetAttenuation(attenuation);

}

