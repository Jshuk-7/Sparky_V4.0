#pragma once

#include <string>

#include <imgui.h>

namespace Sparky::Editor {
	static void TextCentered(const std::string& text)
	{
		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
		ImGui::Text(text.c_str());
	}
}