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
	};

	static void ToggleFullScreenSceneView(SceneFullscreenViewInfo& viewInfo)
	{
		static b8 fullscreenSceneView{};
		fullscreenSceneView = !fullscreenSceneView;

		if (fullscreenSceneView)
		{
			viewInfo.showScenePanel = SP_TRUE;

			viewInfo.showKeyboardShortcutsPanel = SP_FALSE;
			viewInfo.showAboutPanel = SP_FALSE;
			viewInfo.showSettingsPanel = SP_FALSE;
			viewInfo.showSceneHierarchyPanel = SP_FALSE;
			viewInfo.showInspectorPanel = SP_FALSE;
			viewInfo.showConsolePanel = SP_FALSE;
			viewInfo.showContentBrowserPanel = SP_FALSE;
			viewInfo.showStatsPanel = SP_FALSE;
		}
		else
		{
			viewInfo.showSceneHierarchyPanel = SP_TRUE;
			viewInfo.showInspectorPanel = SP_TRUE;
			viewInfo.showConsolePanel = SP_TRUE;
			viewInfo.showScenePanel = SP_TRUE;
		}
	}

	static void RenderScenePanel(
		SceneFullscreenViewInfo& viewInfo,
		b8& viewportFocused,
		b8& windowFullscreen,
		FrameBuffer& framebuffer,
		const vec2& maxWindowSize,
		vec2& windowSize
	) {
		using namespace ImGui;

		SetNextWindowSizeConstraints({ maxWindowSize.x / 3, maxWindowSize.y / 3 }, { maxWindowSize.x, maxWindowSize.y });
		PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		if (Begin("Scene", &viewInfo.showScenePanel, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar))
		{
			viewportFocused = IsWindowFocused();

			if (BeginMenuBar())
			{
				if (MenuItem("Play")) {}

				if (BeginMenu("Tools"))
				{
					if (MenuItem("Stats")) viewInfo.showStatsPanel = !viewInfo.showStatsPanel;

					static b8 fullscreen{ windowFullscreen };
					const i8* text = fullscreen ? "Minimize Scene" : "Maximize Scene";
					if (MenuItem(text))
					{
						ToggleFullScreenSceneView(viewInfo);
						fullscreen = !fullscreen;
					}

					ImGui::EndMenu();
				}

				EndMenuBar();
			}

			BeginChild("GameRender");
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

		PopStyleVar();

		End();
	}
}