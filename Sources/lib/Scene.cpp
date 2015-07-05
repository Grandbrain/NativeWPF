#include "Scene.h"

namespace lib
{
	Scene::Scene(IntPtr handle)
	{
		HWND hwnd = (HWND)handle.ToPointer();
		mRenderer = new Renderer;

		if (mRenderer) mRenderer->Initialize(hwnd);
	}

	Scene::~Scene()
	{
		delete mRenderer;
	}

	void Scene::Resize(IntPtr handle)
	{
		HWND hwnd = (HWND)handle.ToPointer();
		if (mRenderer) mRenderer->Resize(hwnd);
	}

	void Scene::Draw()
	{
		if (mRenderer) mRenderer->Render();
	}
}