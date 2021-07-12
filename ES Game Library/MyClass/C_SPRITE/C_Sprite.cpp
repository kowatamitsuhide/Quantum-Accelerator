#include "C_Sprite.h"

/**
 * @file   Sprite.cpp
 * @brief  Spriteクラスソースファイル
 * @author 中島颯一朗
 * @date   2020/10/1
 */
SpriteManager::SpriteManager()
{
	_sprite.         resize(DRAW_TYPE::TYPE_MAX);
	_sprite_position.resize(DRAW_TYPE::TYPE_MAX);
}
/**
  * @brief 画像を作成する()
  * @param[in] (size)　画像サイズ
  * @param[in] (color) 色
  * @param[in] (position) 座標
  * @return    スロット番号
  */
int SpriteManager::CreateSprite(Vector2 size, Color color, Vector3 position)
{
	SPRITE sprite = GraphicsDevice.CreateSprite((UINT)size.x, (UINT)size.y, PixelFormat_RGBX8888);
	sprite->ColorFill(nullptr, color);

	this->_sprite         [DRAW_TYPE::ALPHA].push_back(sprite);
	this->_sprite_position[DRAW_TYPE::ALPHA].push_back(position);

	this->_sprite_alpha.push_back(0.0f);

	return (this->_sprite [DRAW_TYPE::ALPHA].size() - 1);
}
/**
 * @brief 画像の読み込む()
 * @param[in] (file_name)　画像の名前
 * @param[in] (position)　 画像の座標
 * @return     スロット番号
 */
int SpriteManager::CreateSpriteFromFile(LPCTSTR file_name, Vector3 position)
{
	SPRITE sprite = GraphicsDevice.CreateSpriteFromFile(file_name);
	IDirect3DTexture9* texture = *sprite;

	ASSERT(texture != nullptr && "画像が見つからない!");

	this->_sprite         [DRAW_TYPE::NOMAL].push_back(sprite);
	this->_sprite_position[DRAW_TYPE::NOMAL].push_back(position);

	return (this->_sprite [DRAW_TYPE::NOMAL].size() - 1);
}

int SpriteManager::CreateSpriteFromFileRect(LPCTSTR file_name, Vector3 position)
{
	SPRITE sprite = GraphicsDevice.CreateSpriteFromFile(file_name);
	IDirect3DTexture9* texture = *sprite;

	ASSERT(texture != nullptr && "画像が見つからない!");

	this->_sprite         [DRAW_TYPE::RECTWH].push_back(sprite);
	this->_sprite_position[DRAW_TYPE::RECTWH].push_back(position);

	this->_sprite_rectwh.push_back(RectWH(0, 0, 0, 0));

	return (this->_sprite[DRAW_TYPE::RECTWH].size() - 1);
}

int SpriteManager::CreateSpriteFromFileAlpha(LPCTSTR file_name, Vector3 position)
{
	SPRITE sprite = GraphicsDevice.CreateSpriteFromFile(file_name);
	IDirect3DTexture9* texture = *sprite;

	ASSERT(texture != nullptr && "画像が見つからない!");

	this->_sprite[DRAW_TYPE::ALPHA].push_back(sprite);
	this->_sprite_position[DRAW_TYPE::ALPHA].push_back(position);

	this->_sprite_alpha.push_back(0);

	return (this->_sprite[DRAW_TYPE::ALPHA].size() - 1);
}

/**
 * @brief 画像不透明度を上げる
 * @param[in] (slot)　 スロット番号
 * @return  不透明度が最大値になったらTRUE
 */
bool SpriteManager::BlackOutTrigger(int slot)
{
	ASSERT(slot <= _sprite.size() && "スロット番号存在しません。");
	this->_sprite_alpha[slot] += 0.05f;

	if (this->_sprite_alpha[slot] >= 1.0f){
		this->_sprite_alpha[slot]  = 1.0f;
		return true;
	}
	return false;
}

/**
 *@brief 画像の描画　描画範囲指定</brief>
 */
void SpriteManager::DrawSprite()
{
	for (int i = 0; i < _sprite.size(); i++)
	{
		for (int j = 0; j < _sprite[i].size(); j++)
		{
			switch (i)
			{
			case SpriteManager::NOMAL:
				SpriteBatch.Draw(*this->_sprite[i][j], this->_sprite_position[i][j]);
				break;
			case SpriteManager::RECTWH:
				SpriteBatch.Draw(*this->_sprite[i][j], this->_sprite_position[i][j], this->_sprite_rectwh[j]);
				break;
			case SpriteManager::ALPHA:
				SpriteBatch.Draw(*this->_sprite[i][j], this->_sprite_position[i][j], this->_sprite_alpha[j]);
				break;
			}
		}
	}
};


