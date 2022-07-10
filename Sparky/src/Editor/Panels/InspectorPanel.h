#pragma once

#include <imgui.h>

#include "Config/Defines.h"

namespace Sparky::Editor {
	static void RenderInspectorPanel(b8& showInspectorPanel)
	{
		using namespace ImGui;

		f32 pos[3]{};
		f32 rot[3]{};
		f32 scale[3]{};
		i8 name[30]{};

		if (Begin("Inspector", &showInspectorPanel, ImGuiWindowFlags_NoCollapse))
		{
			BeginChild("Inspector");

			InputText("Name", name, 30);
			Spacing();

			Text("Transform");
			SliderFloat3("Position", pos, -10, 10, "%.2f");
			SliderFloat3("Rotation", rot, -10, 10, "%.2f");
			SliderFloat3("Scale", scale, -10, 10, "%.2f");
			Spacing();
			Separator();
			Text("Box Collider");
			SliderFloat3("Center", pos, -10, 10, "%.2f");

			EndChild();
		}

		End();
	}
}