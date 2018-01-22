#include <d2d1.h>

namespace lib
{
	class Renderer
	{
	public:

		~Renderer()
		{
			if (factory) factory->Release();
			if (target) target->Release();
		}

		bool Initialize(HWND handle, int width, int height)
		{
			if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory)))
				return false;

			return SUCCEEDED(factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(handle, D2D1::SizeU(width, height)), &target));
		}

		void Render()
		{
			if (!target) return;
			target->BeginDraw();
			target->Clear(D2D1::ColorF(D2D1::ColorF::Orange));
			target->EndDraw();
		}

		void Resize(int width, int height)
		{
			if (!target) return;
			D2D1_SIZE_U size = D2D1::SizeU(width, height);
			target->Resize(size);
		}

	private:

		ID2D1Factory* factory;
		ID2D1HwndRenderTarget* target;
	};

	public ref class Scene
	{
	public:

		Scene(System::IntPtr handle, int width, int height)
		{
			renderer = new Renderer;
			if (renderer) renderer->Initialize((HWND)handle.ToPointer(), width, height);
		}

		~Scene()
		{
			delete renderer;
		}

		void Resize(int width, int height)
		{
			if (renderer) renderer->Resize(width, height);
		}

		void Draw()
		{
			if (renderer) renderer->Render();
		}

	private:

		Renderer* renderer;
	};
}