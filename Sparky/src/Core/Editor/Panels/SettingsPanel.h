#pragma once

#include <imgui.h>

#include "Core/Editor/EditorTools.h"
#include "Core/Editor/EditorColors.h"
#include "Config/Defines.h"

namespace Sparky::Editor {
	static void RenderSettingsPanel(b8& showSettingsPanel, b8& vsync, b8& debug)
	{
		using namespace ImGui;

		SetNextWindowSizeConstraints({ 600, 400 }, { 800, 600 });
		if (Begin("Settings", &showSettingsPanel, ImGuiWindowFlags_NoCollapse))
		{
			for (u32 i = 0; i < 2; i++) Spacing();

			if (BeginChild("Settings"))
			{
				TextCentered("Editor"); Separator(); Spacing();
				if (BeginMenu("Theme"))
				{
					if (MenuItem("Sparky Gray")) Editor::StyleColorsSparkyGray();
					if (MenuItem("Light Gray")) Editor::StyleColorsLightGray();
					if (MenuItem("Original Dark")) StyleColorsDark();
					if (MenuItem("Retro Classic")) StyleColorsClassic();
					if (MenuItem("Light")) StyleColorsLight();

					ImGui::EndMenu();
				}

				for (u32 i = 0; i < 8; i++) Spacing();

				TextCentered("Graphics"); Separator(); Spacing();
				Checkbox("VSYNC", &vsync);
				Checkbox("Debug Mode", &debug);

				EndChild();
			}
		}

		End();
	}
}