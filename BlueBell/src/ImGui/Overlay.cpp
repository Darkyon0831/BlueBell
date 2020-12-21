#include "Overlay.h"
#include "../Core/BlueBerry.h"
#include "../Math/Vector2D.h"
#include "../Math/Vector3D.h"

#include <imgui.h>

namespace BlueBell
{
	Overlay::Overlay(const char* name)
		: m_variables(0, BlueBerry()->GetAllocator())
		, m_corner(0)
		, m_name(name)
		, m_open(true)
	{

	}

	Overlay::Overlay(std::initializer_list<Variable> initList, const char* name)
		: m_variables(initList, BlueBerry()->GetAllocator())
		, m_corner(0)
		, m_name(name)
		, m_open(true)
	{

	}

	Overlay::~Overlay()
	{

	}

	void Overlay::Render()
	{
		const float DISTANCE = 10.0f;
		ImGuiIO& io = ImGui::GetIO();
		if (m_corner != -1)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImVec2 work_area_pos = viewport->GetWorkPos();   // Instead of using viewport->Pos we use GetWorkPos() to avoid menu bars, if any!
			ImVec2 work_area_size = viewport->GetWorkSize();
			ImVec2 window_pos = ImVec2((m_corner & 1) ? (work_area_pos.x + work_area_size.x - DISTANCE) : (work_area_pos.x + DISTANCE), (m_corner & 2) ? (work_area_pos.y + work_area_size.y - DISTANCE) : (work_area_pos.y + DISTANCE));
			ImVec2 window_pos_pivot = ImVec2((m_corner & 1) ? 1.0f : 0.0f, (m_corner & 2) ? 1.0f : 0.0f);
			ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
			ImGui::SetNextWindowViewport(viewport->ID);
		}
		ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
		if (m_corner != -1)
			window_flags |= ImGuiWindowFlags_NoMove;
		if (ImGui::Begin(m_name, &m_open, window_flags))
		{
			ImGui::Text(m_name);
			ImGui::Separator();
			
			 for (auto it = m_variables.Begin(); it != m_variables.End(); it++)
			 {
				if (it->type == VariableType::Int)
				{
					int* pInt = reinterpret_cast<int*>(it->pMem);
					ImGui::Text("%s: %d", it->name, *pInt);
				}
				else if (it->type == VariableType::Float)
				{
					float* pFloat = reinterpret_cast<float*>(it->pMem);
					ImGui::Text("%s: %.0f", it->name, *pFloat);
				}
				else if (it->type == VariableType::Vector2D)
				{
					BlueBell::Vector2D* pVector2D = reinterpret_cast<BlueBell::Vector2D*>(it->pMem);
					ImGui::Text("%s: %.0f, %.0f", it->name, pVector2D->x, pVector2D->y);
				}
				else if (it->type == VariableType::Vector3D)
				{
					BlueBell::Vector3D* pVector3D = reinterpret_cast<BlueBell::Vector3D*>(it->pMem);
					ImGui::Text("%s: %.0f, %.0f, %.0f", it->name, pVector3D->x, pVector3D->y, pVector3D->z);
				}
			 }

			if (ImGui::BeginPopupContextWindow())
			{
				if (ImGui::MenuItem("Custom",       NULL, m_corner == -1)) m_corner = -1;
				if (ImGui::MenuItem("Top-left",     NULL, m_corner == 0)) m_corner = 0;
				if (ImGui::MenuItem("Top-right",    NULL, m_corner == 1)) m_corner = 1;
				if (ImGui::MenuItem("Bottom-left",  NULL, m_corner == 2)) m_corner = 2;
				if (ImGui::MenuItem("Bottom-right", NULL, m_corner == 3)) m_corner = 3;
				if (m_open && ImGui::MenuItem("Close")) m_open = false;
				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}
}
