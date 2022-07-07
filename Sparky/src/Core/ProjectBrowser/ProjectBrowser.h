#pragma once

#include "Sparky.h"

class ProjectBrowser
{
public:
	ProjectBrowser(Sparky::vec2 windowSize);
	~ProjectBrowser();

	void Run();
private:
	void GUINewFrame();
	void GUIEndFrame();
	void Destroy();

	void TextCentered(const std::string& text);
	void StyleColorsSparkyGray();


	GLFWwindow* m_Window;
};