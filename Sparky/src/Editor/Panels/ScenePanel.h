#pragma once

#include <imgui.h>

#include "Config/Defines.h"
#include "Math/SparkyMath.h"
#include "Graphics/Objects/FrameBuffer/FrameBuffer.h"

namespace Sparky::Editor {
	struct SceneFullscreenViewInfo {
		b8& showAboutPanel;
		b8& showConsolePanel;
		b8& showContentBrowserPanel;
		b8& showInspectorPanel;
		b8& showKeyboardShortcutsPanel;
		b8& showSceneHierarchyPanel;
		b8& showScenePanel;
		b8& showSettingsPanel;
		b8& showStatsPanel;
		b8& showTextEditorPanel;

		b8& viewportFocused;
		b8& windowFullscreen;

		const vec2& maxWindowSize;
		vec2& windowSize;
	};

	static void ToggleFullScreenSceneView(SceneFullscreenViewInfo& viewInfo)
	{
		static b8 fullscreenSceneView{};
		fullscreenSceneView = !fullscreenSceneView;

		if (fullscreenSceneView)
		{
			viewInfo.showScenePanel = true;

			viewInfo.showKeyboardShortcutsPanel = false;
			viewInfo.showAboutPanel = false;
			viewInfo.showSettingsPanel = false;
			viewInfo.showSceneHierarchyPanel = false;
			viewInfo.showInspectorPanel = false;
			viewInfo.showConsolePanel = false;
			viewInfo.showContentBrowserPanel = false;
			viewInfo.showStatsPanel = false;
			viewInfo.showTextEditorPanel = false;
		}
		else
		{
			viewInfo.showSceneHierarchyPanel = true;
			viewInfo.showInspectorPanel = true;
			viewInfo.showConsolePanel = true;
			viewInfo.showScenePanel = true;
		}
	}

	static void RenderScenePanel(SceneFullscreenViewInfo& viewInfo, FrameBuffer& framebuffer)
	{
		using namespace ImGui;

		const vec2& maxWindowSize = viewInfo.maxWindowSize;
		vec2& windowSize = viewInfo.windowSize;

		SetNextWindowSizeConstraints({ maxWindowSize.x / 3, maxWindowSize.y / 3 }, { maxWindowSize.x, maxWindowSize.y });
		PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		if (Begin("Scene", &viewInfo.showScenePanel, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar))
		{
			viewInfo.viewportFocused = IsWindowFocused();

			if (BeginMenuBar())
			{
				if (MenuItem("Play")) {}

				if (BeginMenu("Tools"))
				{
					if (MenuItem("Stats")) viewInfo.showStatsPanel = !viewInfo.showStatsPanel;

					const i8* text = viewInfo.windowFullscreen ? "Minimize Scene" : "Maximize Scene";
					if (MenuItem(text))
					{
						ToggleFullScreenSceneView(viewInfo);
						viewInfo.windowFullscreen = !viewInfo.windowFullscreen;
					}

					ImGui::EndMenu();
				}

				EndMenuBar();
			}

			if (BeginChild("GameRenderer"))
			{
				ImVec2 wsize = GetWindowSize();

				if (windowSize != *((vec2*)&wsize))
				{
					framebuffer.Resize({ windowSize.x, windowSize.y });
					windowSize = { wsize.x, wsize.y };
				}

				auto textureId = framebuffer.GetColorAttachmentId();
				Image(
					(ImTextureID)textureId,
					ImVec2{ windowSize.x, windowSize.y },
					ImVec2{ 0, 1 }, ImVec2{ 1, 0 }
				);

				EndChild();
			}
		}

		PopStyleVar();

		End();
	}
}