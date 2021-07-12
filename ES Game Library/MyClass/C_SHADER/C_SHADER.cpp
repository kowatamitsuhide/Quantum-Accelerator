#include "C_SHADER.h"

CCamera_* CShaderManager::camera = nullptr;
Vector3 CShaderAnimation::animation_attenuation = Vector3(0.9f, 0.01f, 0.f);

/**
 * @file   C_SHADER.cpp
 * @brief  SHADERクラスソースファイル
 * @author 中島颯一朗
 * @date   2020/10/1
 */

 /**
  * @brief 初期化(シェーダーの登録、パラメータ設定)
  * @param[in] (_tex_path) テクスチャの名前
  * @param[in] (_shader_filename)　shaderのファイルネーム
  * @return    (なし)
  */
void CShaderAnimation::ShaderInitialize(LPCTSTR _tex_path, LPCTSTR _shader_filename)
{
	shader = GraphicsDevice.CreateEffectFromFile(_shader_filename);
	ASSERT(shader != nullptr && "sharedネームが違う");

	SPRITE texture = nullptr;
	texture = GraphicsDevice.CreateSpriteFromFile(_tex_path);

	IDirect3DTexture9* texture_assert = *texture;
	ASSERT(texture_assert != nullptr && "モデルのテクスチャの名前が違う");

	shader->SetTexture("modelTex", *texture);
	shader->SetParameter("light_diffuse", camera->GetLight().Diffuse);
	shader->SetParameter("light_ambient", camera->GetLight().Ambient);
	shader->SetParameter("light_specular", camera->GetLight().Specular);
	shader->SetParameter("light_attenuation", animation_attenuation);

	shader->RetisterMaterialByName("model_diffuse",
		"model_ambient",
		"model_specular",
		nullptr,
		nullptr,
		nullptr);
}

/**
  * @brief 描画(モデルにシェーダーを適応する)
  * @param[in] (alpha)     不透明
  * @param[in] (position)　座標
  * @return    (なし)
  */
EFFECT CShaderAnimation::ShaderDraw(float alpha, Vector3 position) {
	ASSERT(alpha <= 1.0f && "alphaの値は1未満");

	shader->SetTechnique("ANIME");
	shader->SetParameter("light_pos", position + light_pos_correction);
	shader->SetParameter("cam_pos", camera->GetCamera().GetPosition());
	Matrix world = animation_model->GetWorldMatrix();
	Matrix viewproj = camera->GetCamera().GetViewProjectionMatrix();
	shader->SetParameter("world", world);
	shader->SetParameter("wvp", world * viewproj);
	shader->SetParameter("viewProjection", viewproj);
	shader->SetParameter("anime_alpha", alpha);

	animation_model->RegisterBoneMatricesByName(shader, "WorldMatrixArray", "NumBones");

	return shader;
}

/**
  * @brief モデル情報
  * @return    (なし)
  */
void CShaderAnimation::IsModelPass(ANIMATIONMODEL _animation_model)
{
	animation_model = _animation_model;
	return;
}

/**
  * @brief 減数
  * @return (なし)
  */
void CShaderAnimation::SetAttenuation(float _set_attenuation)
{
	animation_attenuation = (Vector3_One * _set_attenuation);
	shader->SetParameter("light_attenuation", animation_attenuation);
	return;
}

//C_SHADER_MODEL設定

Vector3 CShaderModel::model_attenuation = Vector3(0.f,0.f,0.f);

/**
 * @brief 初期化(シェーダーの登録、パラメータ設定)
 * @param[in] (_tex_path) テクスチャの名前
 * @param[in] (_shader_filename)　shaderのファイルネーム
 * @return    (なし)
 */
void CShaderModel::ShaderInitialize(LPCTSTR tex_path, LPCTSTR _shader_filename)
{
	shader = GraphicsDevice.CreateEffectFromFile(_shader_filename);

	SPRITE texture = nullptr;
	texture = GraphicsDevice.CreateSpriteFromFile(tex_path);
	shader->SetTexture("modelTex", *texture);
	shader->SetParameter("light_diffuse", camera->GetLight().Diffuse);
	shader->SetParameter("light_ambient", camera->GetLight().Ambient);
	shader->SetParameter("light_specular", camera->GetLight().Specular);

	shader->RetisterMaterialByName("model_diffuse",
		"model_ambient",
		"model_specular",
		nullptr,
		nullptr,
		nullptr);
}
/**
  * @brief 描画(モデルにシェーダーを適応する)
  * @param[in] (alpha)     不透明
  * @param[in] (position)　座標
  * @return    (なし)
  */
EFFECT CShaderModel::ShaderDraw(float alpha, Vector3 position)
{
	ASSERT(alpha <= 1.0f && "alphaの値は1未満");
	shader->SetTechnique("MODEL");
	shader->SetParameter("light_pos", position + light_pos_correction);
	shader->SetParameter("cam_pos", camera->GetCamera().GetPosition());
	Matrix world = model->GetWorldMatrix();
	Matrix viewproj = camera->GetCamera().GetViewProjectionMatrix();
	shader->SetParameter("world", world);
	shader->SetParameter("wvp", world * viewproj);
	shader->SetParameter("viewProjection", viewproj);
	shader->SetParameter("model_alpha", alpha);

	return shader;
}

void CShaderModel::IsModelPass(MODEL _model)
{
	model = _model;
	return;
}
/**
  * @brief 減数
  * @return (なし)
  */
void CShaderModel::SetAttenuation(float _get_attenuation)
{
	model_attenuation = Vector3_One * _get_attenuation;
	shader->SetParameter("light_attenuation", model_attenuation);
	return;
};

