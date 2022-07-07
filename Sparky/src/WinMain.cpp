#include <Windows.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Sparky.h"
#include "Core/ProjectBrowser/ProjectBrowser.h"

Sparky::i32 WINAPI WinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPSTR lpCmdLine,
	_In_     Sparky::i32 nShowCmd
) {
	/*Sparky::Application* app = Sparky::Application::MakeInstance();*/

	try
	{
		ProjectBrowser browser(Sparky::vec2(800, 500));
		browser.Run();
		/*app->Run();*/
	}
	catch (const Sparky::SparkyException& err)
	{
		SP_FATAL(err.what());
		return SP_EXIT_FAILURE;
	}

	/*if (app != SP_NULL_HANDLE)
		delete app;*/

	return SP_EXIT_SUCCESS;
}