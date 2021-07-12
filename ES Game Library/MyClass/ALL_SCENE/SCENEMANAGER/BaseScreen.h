#pragma once
#include "../../../ESGLib.h"
#include "../../C_INPUT/Input.h"

class BaseScene {
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw3D() = 0;
	virtual void Draw2D() = 0;
	virtual void DrawAlpha3D() = 0;

	virtual void DrawEnd() {};

	BaseScene() {};
	virtual ~BaseScene() 
	{
		MediaManager.ReleaseAllMedia();
		GraphicsDevice.ReleaseAllRenderTargets();
		GraphicsDevice.ReleaseAllStateBlocks();
		GraphicsDevice.ReleaseAllFonts();
		GraphicsDevice.ReleaseAllSprites();
		GraphicsDevice.ReleaseAllAnimationModels();
		GraphicsDevice.ReleaseAllModels();
		GraphicsDevice.ReleaseAllVertexBuffers();
		GraphicsDevice.ReleaseAllEffects();

		SoundDevice.ReleaseAllMusics();
		SoundDevice.ReleaseAllSounds();
	};
};
