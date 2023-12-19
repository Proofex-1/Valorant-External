#include "../main.h"
#include "../blabla/icons.h"
#include "../blabla/fonthelper.h"
#include "../blabla/Images.h"

namespace Discord
{
	static int dc = 0;
}
void valthe()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowMinSize = ImVec2(240, 350);

	// Renkler
	ImVec4 primaryColor = ImVec4(0.08f, 0.40f, 0.74f, 1.00f);
	ImVec4 secondaryColor = ImVec4(0.95f, 0.47f, 0.20f, 1.00f);
	ImVec4 backgroundColor = ImVec4(0.11f, 0.11f, 0.15f, 1.00f);
	ImVec4 textColor = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);

	// Ayarlar
	style.Colors[ImGuiCol_Text] = textColor;
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = backgroundColor;
	style.Colors[ImGuiCol_ChildBg] = backgroundColor;
	style.Colors[ImGuiCol_PopupBg] = backgroundColor;
	style.Colors[ImGuiCol_Border] = ImVec4(0.50f, 0.50f, 0.50f, 0.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = primaryColor;
	style.Colors[ImGuiCol_FrameBgActive] = secondaryColor;
	style.Colors[ImGuiCol_TitleBg] = primaryColor;
	style.Colors[ImGuiCol_TitleBgActive] = primaryColor;
	style.Colors[ImGuiCol_TitleBgCollapsed] = primaryColor;
	style.Colors[ImGuiCol_MenuBarBg] = backgroundColor;
	style.Colors[ImGuiCol_ScrollbarBg] = backgroundColor;
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = primaryColor;
	style.Colors[ImGuiCol_SliderGrab] = primaryColor;
	style.Colors[ImGuiCol_SliderGrabActive] = secondaryColor;
	style.Colors[ImGuiCol_Button] = primaryColor;
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.48f, 0.86f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.22f, 0.44f, 0.80f, 1.00f);
	style.Colors[ImGuiCol_Header] = primaryColor;
	style.Colors[ImGuiCol_HeaderHovered] = primaryColor;
	style.Colors[ImGuiCol_HeaderActive] = primaryColor;
	style.Colors[ImGuiCol_Separator] = ImVec4(0.32f, 0.32f, 0.32f, 0.50f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.32f, 0.32f, 0.32f, 0.78f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	style.Colors[ImGuiCol_ResizeGripHovered] = primaryColor;
	style.Colors[ImGuiCol_ResizeGripActive] = secondaryColor;
	style.Colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_TabHovered] = primaryColor;
	style.Colors[ImGuiCol_TabActive] = primaryColor;
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = primaryColor;
	style.Colors[ImGuiCol_PlotLines] = primaryColor;
	style.Colors[ImGuiCol_PlotLinesHovered] = secondaryColor;
	style.Colors[ImGuiCol_PlotHistogram] = primaryColor;
	style.Colors[ImGuiCol_PlotHistogramHovered] = secondaryColor;
	style.Colors[ImGuiCol_TextSelectedBg] = primaryColor;
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);

	// Döndürülebilir çubuk renkleri
	style.Colors[ImGuiCol_TabHovered] = primaryColor;
	style.Colors[ImGuiCol_TabActive] = primaryColor;
	style.Colors[ImGuiCol_HeaderHovered] = primaryColor;
	style.Colors[ImGuiCol_HeaderActive] = primaryColor;
	style.Colors[ImGuiCol_ButtonHovered] = primaryColor;
	style.Colors[ImGuiCol_ButtonActive] = primaryColor;
}

void scarlet()
{
		ImGui::SetCursorPos(ImVec2(5, 30));
		ImGui::BeginGroup();
		{
			ImGui::Checkbox("Esp Box", &config.player_box);
			ImGui::Checkbox("Direction ESP", &config.player_view_angle);
			if (!config.player_view_angle)
			{
				ImGui::Checkbox("Head Box", &config.circlehead); //Head Box ile Diretion ESP karışmasın diye
			}
			else
			{
				config.circlehead = false;
			}
			ImGui::Checkbox("Skeleton Esp", &config.player_skeleton);
			ImGui::Checkbox("Esp Line", &config.player_snapline);
			ImGui::Checkbox("Distance ESP", &config.player_distance);
			ImGui::Checkbox("Healthbar", &config.player_healthbar);
			ImGui::Checkbox("Agent Names", &config.agentnames);
			ImGui::Checkbox("Radar", &config.radar);
			ImGui::Checkbox("Ignore Dormant", &config.player_ignore_dormant);
			ImGui::Combo("ESP Settings", &config.esptype, type, IM_ARRAYSIZE(type));
			ImGui::Combo("Line Settings", &config.linetype, linetype, IM_ARRAYSIZE(linetype));
			ImGui::Checkbox("Aim Enable", &config.aimenable);
			ImGui::Combo("Aim Type", &config.aimtype, aimtype, IM_ARRAYSIZE(aimtype));
			if (config.aimenable)
			{
				if (config.aimenable && config.aimtype == 0)
				{
					ImGui::Checkbox("Draw Fov", &config.aimbot_draw_fov);
					ImGui::Combo("Aim Key", &config.aimbotkey, optKey, IM_ARRAYSIZE(optKey));
					ImGui::Combo("Aim Target", &config.aimboness, aimbone, IM_ARRAYSIZE(aimbone));
					ImGui::SliderFloat("Aim Speed", &config.aimbot_smooth, 6, 25);
					ImGui::SliderFloat("Aim Fov", &config.aimbot_fov, 10, 80);
				}
				if (config.aimenable && config.aimtype == 1)
				{
					ImGui::Checkbox("Recoil Control System", &config.rcs);
					ImGui::Checkbox("Draw Fov", &config.aimbot_draw_fov);
					ImGui::Combo("Aim Key", &config.aimbotkey, optKey, IM_ARRAYSIZE(optKey));
					ImGui::Combo("Aim Target", &config.aimboness, aimbone, IM_ARRAYSIZE(aimbone));
					ImGui::SliderFloat("Aim Speed", &config.aimbot_smooth, 1, 20);
					if (config.aimbot_smooth <= 2.0f)
					{
						ImGui::SliderFloat("Aim Fov", &config.aimbot_fov, 10, 200);
					}

					if (config.aimbot_smooth > 2.0f)
					{
						ImGui::SliderFloat("Aim Fov", &config.aimbot_fov, 10, 600);
					}
				}
			}
		}
		ImGui::EndGroup();

}