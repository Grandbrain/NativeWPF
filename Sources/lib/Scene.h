#include <memory>
#include "Renderer.h"

using namespace System;

namespace lib
{
	public ref class Scene
	{
	public:

		Scene(IntPtr);
	    ~Scene();

		void Resize(IntPtr);
		void Draw();

	private:

		Renderer* mRenderer;
	};
}