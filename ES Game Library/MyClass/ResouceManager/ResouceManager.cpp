#include "ResouceManager.h"

SPRITE ResouceManager::LordSpriteFile(tstring sprite_file_name)
{
	auto&& it = _resouces_sprite.find(sprite_file_name);
	if (it != _resouces_sprite.end())	{return it->second;}
	else
	{
		SPRITE sprite = GraphicsDevice.CreateSpriteFromFile(sprite_file_name.c_str());
		_resouces_sprite.emplace_hint(_resouces_sprite.end(), sprite_file_name, sprite);
		return _resouces_sprite[sprite_file_name];
	}
}

MODEL ResouceManager::LoadModelFile(tstring model_file_name)
{
	auto&& it = _resouces_model.find(model_file_name);
	if (it != _resouces_model.end()){return it->second;}
	else
	{
		MODEL model = GraphicsDevice.CreateModelFromFile(model_file_name.c_str());
		_resouces_model.emplace_hint(_resouces_model.end(), model_file_name, model);
		return _resouces_model[model_file_name];
	}
}

ANIMATIONMODEL ResouceManager::LoadAnimationModelFile(tstring animation_model_name)
{
	auto&& it = _resouces_animation_model.find(animation_model_name);
	if (it != _resouces_animation_model.end()){return it->second;}
	else
	{
		ANIMATIONMODEL animationmodel = GraphicsDevice.CreateAnimationModelFromFile(animation_model_name.c_str());
		_resouces_animation_model.emplace_hint(_resouces_animation_model.end(), animation_model_name, animationmodel);
		return _resouces_animation_model[animation_model_name];
	}
}

FONT ResouceManager::LordFontFile(tstring font_file_name,float size)
{
	auto&& it = _resouces_font.find(font_file_name);
	if (it != _resouces_font.end()){return it->second;}
	else
	{
		FONT font = GraphicsDevice.CreateSpriteFont(font_file_name.c_str(), size);
		_resouces_font.emplace_hint(_resouces_font.end(), font_file_name, font);
		return _resouces_font[font_file_name];
	}
}

EFFECT ResouceManager::LordEffectFile(tstring effect_file_name)
{
	auto&& it = _resouces_effect.find(effect_file_name);
	if (it != _resouces_effect.end()){return it->second;}
	else
	{
		EFFECT effect = GraphicsDevice.CreateEffectFromFile(effect_file_name.c_str());
		_resouces_effect.emplace_hint(_resouces_effect.end(), effect_file_name, effect);
		return _resouces_effect[effect_file_name];
	}
}

SOUND ResouceManager::LordSoundFile(tstring sound_file_name)
{
	auto&& it = _resouces_sound.find(sound_file_name);
	if (it != _resouces_sound.end()){return it->second;}
	else
	{
		SOUND sound = SoundDevice.CreateSoundFromFile(const_cast<LPTSTR>(sound_file_name.c_str()));
		_resouces_sound.emplace_hint(_resouces_sound.end(), sound_file_name, sound);
		return _resouces_sound[sound_file_name];
	}
}

MUSIC ResouceManager::LordMusicFile(tstring music_file_name)
{
	auto&& it = _resouces_music.find(music_file_name);
	if (it != _resouces_music.end()){return it->second;}
	else
	{
		MUSIC music = SoundDevice.CreateMusicFromFile(const_cast<LPTSTR>(music_file_name.c_str()));
		_resouces_music.emplace_hint(_resouces_music.end(), music_file_name, music);
		return _resouces_music[music_file_name];
	}
}

MEDIA ResouceManager::LordMediaFile(tstring media_file_name)
{
	auto&& it = _resouces_media.find(media_file_name);
	if (it != _resouces_media.end()){return it->second;}
	else
	{
		MEDIA media = MediaManager.CreateMediaFromFile(const_cast<LPTSTR>(media_file_name.c_str()));
		_resouces_media.emplace_hint(_resouces_media.end(), media_file_name, media);
		return _resouces_media[media_file_name];
	}
}

EFFEKSEER ResouceManager::LordEffekseerFile(tstring effekseer_file_name)
{
	auto&& it = _resouces_effekseer.find(effekseer_file_name);
	if (it != _resouces_effekseer.end()){return it->second;}
	else
	{
		EFFEKSEER effekseer = Effekseer.CreateEffectFromFile(const_cast<LPTSTR>(effekseer_file_name.c_str()));
		_resouces_effekseer.emplace_hint(_resouces_effekseer.end(), effekseer_file_name, effekseer);
		return _resouces_effekseer[effekseer_file_name];
	}
}
