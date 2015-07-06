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

		bool Initialize(HWND handle)
		{
			RECT rect;
			if (!GetClientRect(handle, &rect)) return false;

			if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory)))
				return false;

			return SUCCEEDED(factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(handle, D2D1::SizeU(rect.right - rect.left,
				rect.bottom - rect.top)), &target));
		}

		void Render()
		{
			if (!target) return;
			target->BeginDraw();
			target->Clear(D2D1::ColorF(D2D1::ColorF::Orange));
			target->EndDraw();
		}

		void Resize(HWND handle)
		{
			if (!target) return;
			RECT rect;
			if (!GetClientRect(handle, &rect)) return;
			D2D1_SIZE_U size = D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top);
			target->Resize(size);
		}

	private:

		ID2D1Factory* factory;
		ID2D1HwndRenderTarget* target;
	};

	public ref class Scene
	{
	public:

		Scene(System::IntPtr handle)
		{
			renderer = new Renderer;
			if (renderer) renderer->Initialize((HWND)handle.ToPointer());
		}

		~Scene()
		{
			delete renderer;
		}

		void Resize(System::IntPtr handle)
		{
			HWND hwnd = (HWND)handle.ToPointer();
			if (renderer) renderer->Resize(hwnd);
		}

		void Draw()
		{
			if (renderer) renderer->Render();
		}

	private:

		Renderer* renderer;
	};
}