#pragma once

#include <imgui.h>

#include "Core/Editor/EditorTools.h"
#include "Config/Defines.h"

namespace Sparky::Editor {
	static void RenderAboutPanel(b8& showAboutPanel)
	{
		using namespace ImGui;

		SetNextWindowSize({ 500, 350 });
		if (Begin("About Sparky", &showAboutPanel, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
		{
			BeginChild("About");

			TextCentered("Welcome to Sparky Game Engine.");
			TextCentered("Sparky is currently under development");

			EndChild();
		}

		End();
	}
}