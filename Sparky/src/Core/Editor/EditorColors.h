#pragma once

#include <imgui.h>

namespace Sparky::Editor {
	static void StyleColorsLightGray() noexcept
	{
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
		colors[ImGuiCol_WindowBg] = ImVec4(.2, .2, .2, .95);
		colors[ImGuiCol_PopupBg] = ImVec4(.15, .15, .15, 1);
		colors[ImGuiCol_Button] = ImVec4(.2, .4, .75, .65);
		colors[ImGuiCol_TitleBg] = ImVec4(.1, .1, .1, 1);
		colors[ImGuiCol_TitleBgActive] = ImVec4(.15, .15, .15, 1);
		colors[ImGuiCol_Tab] = ImVec4(.2, .4, .75, .5);
		colors[ImGuiCol_TabActive] = ImVec4(.2, .4, .75, 1);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(.2, .4, .75, .65);
		colors[ImGuiCol_FrameBg] = ImVec4(.5, .5, .5, .25);
		colors[ImGuiCol_MenuBarBg] = ImVec4(.15, .15, .15, 1);
	}

	static void StyleColorsSparkyGray() noexcept
	{
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
		colors[ImGuiCol_WindowBg] = ImVec4(.1, .105, .11, .90);
		colors[ImGuiCol_MenuBarBg] = ImVec4(.15, .15, .15, 1);

		colors[ImGuiCol_Header] = ImVec4(.2, .205, .21, 1);
		colors[ImGuiCol_HeaderHovered] = ImVec4(.3, .305, .31, 1);
		colors[ImGuiCol_HeaderActive] = ImVec4(.15, .1505, .151, 1);

		colors[ImGuiCol_Button] = ImVec4(.2, .205, .21, 1);
		colors[ImGuiCol_ButtonHovered] = ImVec4(.3, .305, .31, 1);
		colors[ImGuiCol_ButtonActive] = ImVec4(.15, .1505, .151, 1);

		colors[ImGuiCol_FrameBg] = ImVec4(.2, .205, .21, 1);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(.3, .305, .31, 1);
		colors[ImGuiCol_FrameBgActive] = ImVec4(.15, .1505, .151, 1);

		colors[ImGuiCol_Tab] = ImVec4(.15, .1505, .151, 1);
		colors[ImGuiCol_TabHovered] = ImVec4(.38, .3805, .381, 1);
		colors[ImGuiCol_TabActive] = ImVec4(.28, .2805, .281, 1);
		colors[ImGuiCol_TabUnfocused] = ImVec4(.15, .1505, .151, 1);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(.2, .205, .21, 1);

		colors[ImGuiCol_PopupBg] = ImVec4(.15, .15, .15, 1);

		colors[ImGuiCol_TitleBg] = ImVec4(.15, .1505, .151, 1);
		colors[ImGuiCol_TitleBgActive] = ImVec4(.15, .1505, .151, 1);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(.15, .1505, .151, 1);
	}
}