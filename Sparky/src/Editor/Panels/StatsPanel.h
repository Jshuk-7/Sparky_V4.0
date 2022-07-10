#pragma once

#include <algorithm>

#include <imgui.h>

#include "Config/Defines.h"
#include "Graphics/Renderer/Renderer.h"

namespace Sparky::Editor {
	static void RenderStatsPanel(b8& showStatsPanel, const b8& vsync, const b8& glCoreProfile, const RendererStatistics& stats, u32 frameCount, const Version& glContextVersion)
	{
		using namespace ImGui;

		SetNextWindowSizeConstraints({  }, { 500, 400 });
		if (Begin("Stats", &showStatsPanel, ImGuiWindowFlags_NoCollapse))
		{
			if (TreeNode("Renderer"))
			{
				TreePop();
				Indent();
				Bullet(); Text("Draw Calls: %i", stats.drawCalls);
				Bullet(); Text("Triangle Count: %i", stats.triangleCount);
				Bullet(); Text("Vertices: %i", stats.vertices);
				Unindent();
			}

			for (u32 i = 0; i < 4; i++) Spacing();

			if (TreeNode("Engine"))
			{
				TreePop();
				Indent();
				Bullet(); Text("FPS: %i", std::clamp(frameCount / (u32)glfwGetTime(), (u32)0, (u32)100000));
				Bullet(); Text(vsync ? "VSYNC: Enabled" : "VSYNC: Disabled");
				const i8* text = glCoreProfile ? "OpenGL Version: %i.%i.%i core" : "OpenGL Version: %i.%i.%i";
				Bullet(); Text(text, glContextVersion.major, glContextVersion.minor, glContextVersion.patch);
				Unindent();
			}
		}

		ImGui::End();
	}
}