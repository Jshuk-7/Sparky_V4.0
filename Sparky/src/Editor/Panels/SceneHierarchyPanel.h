#pragma once

#include <imgui.h>

#include "Config/Defines.h"

namespace Sparky::Editor {
	static void RenderSceneHierarchyPanel(b8& showSceneHierarchyPanel)
	{
		using namespace ImGui;

		static ImGuiDir_ dir{ ImGuiDir_Right };

		if (Begin("Scene Hierarchy", &showSceneHierarchyPanel, ImGuiWindowFlags_NoCollapse))
		{
			BeginChild("Scene Hierarchy");
			if (ArrowButton("Hello", dir))
			{
				if (dir == ImGuiDir_Down) dir = ImGuiDir_Right;
				else if (dir == ImGuiDir_Right) dir = ImGuiDir_Down;
			}

			EndChild();
		}

		End();
	}
}