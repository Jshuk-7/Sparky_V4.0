#pragma once

#include <imgui.h>

namespace Sparky::Editor {
	static void RenderKeyboardShortcutsPanel(b8& showKeyboardShortcutsPanel)
	{
		using namespace ImGui;

		SetNextWindowSizeConstraints({ 600, 400 }, { 800, 600 });
		if (Begin("Keyboard Shortcuts", &showKeyboardShortcutsPanel, ImGuiWindowFlags_NoCollapse))
		{
			BeginChild("Keyboard");

			Bullet(); Text("Maximize Scene: Ctrl+Space");


			EndChild();
		}

		End();
	}
}