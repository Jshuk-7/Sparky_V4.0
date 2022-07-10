#pragma once

#include <imgui.h>

#include "Utilities/Log/Log.h"

namespace Sparky::Editor {
	static void RenderConsolePanel(b8& showConsolePanel) noexcept
	{
		using namespace ImGui;

		auto logs = Log::GetLogs();

		if (Begin("Console", &showConsolePanel, ImGuiWindowFlags_NoCollapse))
		{
			BeginChild("Console");

			auto logs = Log::GetLogs();

			if (!logs.empty())
			{
				for (const auto& log : logs)
				{
					Text(Log::s_LogBaseMessage); SameLine(); Text(log.c_str());
				}
			}

			EndChild();
		}

		End();
	}
}