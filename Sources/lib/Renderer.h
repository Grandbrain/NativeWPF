#include <d2d1.h>
#include "Pointer.h"

namespace lib
{
	class Renderer
	{
	public:

		bool Initialize(HWND);
		void Render();
		void Resize(HWND);

	private:

		Pointer<ID2D1Factory> mFactory;
		Pointer<ID2D1HwndRenderTarget> mTarget;
	};
}