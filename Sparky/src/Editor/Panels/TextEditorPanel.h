#pragma once

#include <imgui.h>

#include "Config/Defines.h"

namespace Sparky::Editor {
	static void RenderTextEditorPanel(b8& showTextEditorPanel)
	{
		using namespace ImGui;

		SetNextWindowSizeConstraints({}, {});
		if (Begin("Text Editor", &showTextEditorPanel, ImGuiWindowFlags_NoCollapse))
		{
			BeginChild("TextEditor");
			
			

			EndChild();
		}

		End();
	}
}