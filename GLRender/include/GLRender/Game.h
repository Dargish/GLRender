#include <GLRender/DataTypes.h>
#include <GLRender/Graphics/Window.h>

namespace glr
{
	class GLRENDERAPI Game
	{
	public:
		Game();
		virtual ~Game();

		void createWindow(Window& window, uint width, uint height, string title = "GLRender");
		void registerWindow(Window& window);
	};
}