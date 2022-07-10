#pragma once

#include <imgui.h>

#include "Config/Defines.h"
#include "Editor/EditorTools.h"
#include "Utilities/Log/Log.h"

namespace Sparky::Editor {
	struct MainMenuBarPanelInfo {
		b8& showAboutPanel;
		b8& showConsolePanel;
		b8& showContentBrowserPanel;
		b8& showInspectorPanel;
		b8& showKeyboardShortcutsPanel;
		b8& showSceneHierarchyPanel;
		b8& showScenePanel;
		b8& showSettingsPanel;
		b8& showTextEditorPanel;
	};

	static void RenderMainMenuBar(MainMenuBarPanelInfo& panels)
	{
		using namespace ImGui;

		if (BeginMainMenuBar())
		{
			if (BeginMenu("File"))
			{
				if (MenuItem("New", "Ctrl+N")) {}
				if (MenuItem("Open", "Ctrl+O")) {}
				if (MenuItem("Save As...", "Ctrl+Shift+S")) {}
				if (MenuItem("Settings")) panels.showSettingsPanel = !panels.showSettingsPanel;
				if (MenuItem("Exit")) SP_EXIT(SP_EXIT_SUCCESS);

				ImGui::EndMenu();
			}

			if (BeginMenu("Edit"))
			{
				if (MenuItem("Undo", "Ctrl+Z")) {}
				if (MenuItem("Redo", "Ctrl+Shift+Z")) {}

				ImGui::EndMenu();
			}

			if (BeginMenu("Window"))
			{
				if (MenuItem("Console"))          panels.showConsolePanel         = !panels.showConsolePanel;
				if (MenuItem("Content Browser"))  panels.showContentBrowserPanel  = !panels.showContentBrowserPanel;
				if (MenuItem("Inspector"))        panels.showInspectorPanel       = !panels.showInspectorPanel;
				if (MenuItem("Scene"))            panels.showScenePanel           = !panels.showScenePanel;
				if (MenuItem("Scene Hierarchy"))  panels.showSceneHierarchyPanel  = !panels.showSceneHierarchyPanel;
				if (MenuItem("Text Editor"))      panels.showTextEditorPanel      = !panels.showTextEditorPanel;

				ImGui::EndMenu();
			}

			if (BeginMenu("Help"))
			{
				if (MenuItem("Keyboard Shortcuts")) panels.showKeyboardShortcutsPanel = !panels.showKeyboardShortcutsPanel;
				if (MenuItem("About Sparky")) panels.showAboutPanel = !panels.showAboutPanel;

				ImGui::EndMenu();
			}

			TextCentered(Log::GetCurrentTime());

			EndMainMenuBar();
		}
	}
}