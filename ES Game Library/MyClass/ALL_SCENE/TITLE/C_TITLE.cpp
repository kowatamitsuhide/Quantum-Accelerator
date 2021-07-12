#include "C_TITLE.h"
#include "../SCENEMANAGER/SceneManager.h"
#include <algorithm>


void C_TITLE::Initialize()
{
	Add_Sprite(_T("新タイトル　素材/background.png"));
	moji  = GraphicsDevice.CreateSpriteFromFile(_T("新タイトル　素材/accelerator.png"));
	moji2 = GraphicsDevice.CreateSpriteFromFile(_T("新タイトル　素材/quantum.png"));
	moji3 = GraphicsDevice.CreateSpriteFromFile(_T("SPRITE/start.png"));
	iro = 0; moji_x = 0;

}

void C_TITLE::Update()
{
	moji_x += 20;
	if (moji_x >= 1280) { moji_x = 1280;   iro += 0.01; }

	if (Input.GetKeybordInputDown(Keys_Enter))
	{
		SceneManager::ChangeScene(SceneManager::MAIN);
	}

	return;
}

void C_TITLE::Draw2D()
{
	std::for_each(sprite_list_name.begin(), sprite_list_name.end(), [](SPRITE& _sprite)
		{SpriteBatch.Draw(*_sprite, Vector3(0, 0, 0)); });

	SpriteBatch.Draw(*moji, Vector3(1280 - moji_x, 0, 0));
	SpriteBatch.Draw(*moji2, Vector3(-1280 + moji_x, 0, 0));
	SpriteBatch.Draw(*moji3, Vector3(0, 100, 0), iro);

}

void C_TITLE::Add_Sprite(LPCTSTR _sprite_name)
{
	sprite = GraphicsDevice.CreateSpriteFromFile(_sprite_name);
	sprite_list_name.push_back(sprite);

}