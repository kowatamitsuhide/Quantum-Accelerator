#pragma once
#include "../../ESGLib.h"
#include "../C_SHADER/C_SHADER.h"
#include "../CPLAYERDATA/CPlayerData.h"

//キャラクター生成クラス

class ModelBase
{
protected:
	Material SetMaterial(Color color);

	virtual void SetModel(LPCTSTR model_filename)    = 0;
	virtual void SetShader(LPCTSTR model_filename)   = 0;
	virtual void SetMove(Vector3  move_position)     = 0;
	virtual void SetPosition(Vector3 position)       = 0;
	virtual void SetRotation(Vector3 rotation)       = 0;
	virtual void SetScale(float character_scale)     = 0;
	virtual void SetDirection(Quaternion quaternion) = 0;
};

class AnimationModel : public ModelBase
{
public:
	//アニメーションのパラメータの設定関数

	virtual void SetModel(LPCTSTR model_filename)    override;
	virtual void SetShader(LPCTSTR model_filename)   override;
	virtual void SetMove(Vector3  move_position)     override { _animation_model->Move(move_position);   };
	virtual void SetPosition(Vector3 position)       override { _animation_model->SetPosition(position); };
	virtual void SetRotation(Vector3 rotation)       override { _animation_model->SetRotation(rotation); };
	virtual void SetScale(float character_scale)     override { _animation_model->SetScale(character_scale); };
	virtual void SetDirection(Quaternion quaternion) override { _animation_model->SetDirection(quaternion); };

	void SetPlayerState(int new_state);
	void SetAdvanceTime(int generating_time, int animation_speed);

	void SetMateriaI(Color color)           { _animation_model->SetMaterial(SetMaterial(color)); };

	ANIMATIONMODEL GetAnimationModel() { return _animation_model; };

	//アニメーションのパラメータを取得

	Vector3 GetFrontVector() const { return _animation_model->GetFrontVector(); };
	Vector3 GetPosition()    const { return _animation_model->GetPosition();    };

	Quaternion GetDirectionQuaternion() const { return  _animation_model->GetDirectionQuaternion(); };


	//描画タイプ選択　影とシェーダーと普通の３つ　同時に適用ができない
	void DrawShader(float alpha);
	void Draw();
	void DrawShadow();

	int GetPlayerState() const { return _player_state; };

	//影の描画
	Matrix Create_Shadow(const D3DLIGHTTYPE light_type, const Vector3& light, const Vector3& pos, const Vector3& shadow_offset, const Vector3& normal);

	ANIMATIONMODEL _animation_model = nullptr;
private:

	//関数定義

	//変数定義

	int     _player_state    = 0;

	double  _generating_time = 1.0f;
	double  _animation_speed = 60.0f;

	//クラスインスタンスの定義
	std::unique_ptr <CShaderManager> _shader;
};

class Model : public ModelBase
{
public:

	Model();

	//アニメーションのパラメータの設定関数
	virtual void SetModel(LPCTSTR model_filename)    override;

	virtual void SetShader(LPCTSTR model_filename)	 override;
	virtual void SetMove(Vector3  move_position)     override { _model->Move(move_position); };
	virtual void SetPosition(Vector3 position)       override { _model->SetPosition(position); };
	virtual void SetRotation(Vector3 rotation)       override { _model->SetRotation(rotation); };
	virtual void SetScale(float character_scale)     override { _model->SetScale(character_scale); };
	virtual void SetDirection(Quaternion quaternion) override { _model->SetDirection(quaternion); };

	MODEL GetModel() const { return _model; };

	float GetRadius() {float model = _model->GetOBB().Radius.x;};

	void Attenuation(float attenuation);

	void Model::SetModelData(MODEL Model) { _model = Model; 	_model->SetMaterial(SetMaterial(Color(1.0f, 1.0f, 1.0f)));};

	//アニメーションのパラメータを取得

	//描画タイプ選択　静止したモデルなので普通描画だけ
	void Draw();
	void DrawShader(float alpha);

    void SetModels(MODEL model);

private:

	//関数定義

	//変数定義

	MODEL _model = nullptr;

	//クラスインスタンスの定義
	std::unique_ptr <CShaderManager>  _shader;
	std::unique_ptr<IPlayerData>      _iplayer_data;

};