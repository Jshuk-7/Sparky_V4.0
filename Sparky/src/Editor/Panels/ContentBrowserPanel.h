#pragma once

#include <filesystem>

#include <GLFW/glfw3.h>

#include <imgui.h>

#include "Config/Defines.h"

namespace Sparky::Editor {
	/// Once we have projects change this
	static const std::filesystem::path ASSET_PATH = "Assets";

	static void RenderContentBrowserPanel(b8& showContentBrowserPanel, b8& fullscreen, ImFont* font, GLFWwindow* window)
	{
		using namespace ImGui;

		static std::filesystem::path currentDirectory = ASSET_PATH;

		i32 w, h, x, y;
		glfwGetWindowSize(window, &w, &h);
		glfwGetWindowPos(window, &x, &y);

		if (!fullscreen)
		{
			SetNextWindowSize({ (f32)w, 375 });
			SetNextWindowPos({ (f32)x, (f32)h - 50 });
		}

		if (Begin("Content Browser", &showContentBrowserPanel,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
		{
			PushFont(font);
			BeginChild("Browser");

			if (currentDirectory != std::filesystem::path(ASSET_PATH))
			{
				if (Button("<--"))
					currentDirectory = currentDirectory.parent_path();
			}

			for (auto& directoryEntry : std::filesystem::directory_iterator(currentDirectory))
			{
				const auto& path = directoryEntry.path();
				auto relativePath = std::filesystem::relative(path, ASSET_PATH);
				std::string filenameString = relativePath.filename().string();

				if (directoryEntry.is_directory())
				{
					if (Button(filenameString.c_str()))
						currentDirectory /= path.filename();
				}
				else
				{
					if (Button(filenameString.c_str()))
					{
						if (relativePath.extension() == ".glsl")
						{
							showContentBrowserPanel = false;
							//s_ShowTextEditorPanel = true;
							//ShowTextEditor(relativePath);
						}
					}
				}
			}

			EndChild();
			PopFont();
		}

		End();
	}
}