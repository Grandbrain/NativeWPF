
#include "Renderer.h"

namespace lib
{
	bool Renderer::Initialize(HWND handle)
	{
		RECT rect;

		if (!GetClientRect(handle, &rect))
			return false;

		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mFactory)))
			return false;

		if (FAILED(mFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(handle, D2D1::SizeU(rect.right - rect.left,
			rect.bottom - rect.top)), &mTarget)))
			return false;

		return true;
	}

	void Renderer::Render()
	{
		if (!mTarget) return;
		mTarget->BeginDraw();
		mTarget->Clear(D2D1::ColorF(D2D1::ColorF::Orange));
		mTarget->EndDraw();
	}

	void Renderer::Resize(HWND handle)
	{
		if (!mTarget) return;

		RECT rect;

		if (!GetClientRect(handle, &rect))
			return;

		D2D1_SIZE_U size = D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top);
		mTarget->Resize(size);
	}
}