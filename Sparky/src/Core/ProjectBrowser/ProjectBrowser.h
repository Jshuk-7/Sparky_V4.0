#pragma once

#include "Sparky.h"

namespace Sparky {
	class ProjectBrowser
	{
	public:
		ProjectBrowser(vec2 windowSize = vec2(800, 500));

		void Run();
	
	private:
		void ProcessInput();

		void RunGameEngine();

		void GUINewFrame();
		void GUIEndFrame();
		void Destroy();

		void TextCentered(const std::string& text);
		void StyleColorsSparkyGray();

		GLFWwindow* m_Window;
		vec2 m_WindowSize;

	};
}