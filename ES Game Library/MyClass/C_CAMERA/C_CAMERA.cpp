#include "C_CAMERA.h"

void CCamera_::Init()
{
	Effekseer.Attach(GraphicsDevice);

	Color color = (0.5f, 0.5f, 0.5f);

	light.Type      = Light_Directional;
	light.Direction = Vector3_Down + Vector3_Forward;
	light.Diffuse   = color;
	light.Ambient   = color;
	light.Specular  = color;
	light.Position  = Vector3(0, 10, 0);

	cameraPov = 60.0f;

	camera->SetPerspectiveFieldOfView(cameraPov, 16.0f / 9.0f, 0.1f, 100.0f);

	GraphicsDevice.SetLight(light);
	GraphicsDevice.SetCamera(camera);
}

void CCamera_::Update()
{
	cameraPov -= 0.2f;
	cameraPov = this->clamp(cameraPov, 50.0f, 55.0f);

	camera->SetFieldOfViewY(cameraPov);

	camera->SetLookAt(gameObject->transform.position + Vector3(0.0f,0.5f, - 0.90f),gameObject->transform.position + Vector3(0.0f, -0.56f, 4.5f), Vector3_Up);

	Effekseer.Update();

	GraphicsDevice.SetCamera(camera);
}

void CCamera_::DrawEnd()
{
	GraphicsDevice.SetCamera(camera);

	Effekseer.SetCamera(camera);
	Effekseer.Draw();
};


