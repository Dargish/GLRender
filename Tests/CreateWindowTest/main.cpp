#include <GLRender/Game.h>

using namespace glr;

int main()
{
	Game game;

	Window window;

	game.createWindow(window, 1280, 720, "CreateWindowTest");
	window.hide();
	window.show();
	window.destroy();

	return 0;
}
