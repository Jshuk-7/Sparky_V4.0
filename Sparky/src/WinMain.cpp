#include <Windows.h>

#include "Sparky.h"
#include "Core/ProjectBrowser/ProjectBrowser.h"

Sparky::i32 WINAPI WinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPSTR lpCmdLine,
	_In_     Sparky::i32 nShowCmd
) {
	try
	{
		Sparky::ProjectBrowser browser;
		browser.Run();
	}
	catch (const Sparky::SparkyException& err)
	{
		SP_FATAL(err.what());
		SP_EXIT(SP_EXIT_FAILURE);
	}

	SP_EXIT(SP_EXIT_SUCCESS);
}