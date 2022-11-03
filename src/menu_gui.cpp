#include "menu_gui.h"

#include "imgui.h"

#include "spdlog/spdlog.h"

ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
								ImGuiWindowFlags_MenuBar |
								ImGuiWindowFlags_NoCollapse |
								ImGuiWindowFlags_NoMove |
								ImGuiWindowFlags_NoSavedSettings |
								ImGuiWindowFlags_NoResize;

ImGuiTableFlags table_flags = ImGuiTableFlags_ScrollX |
							  ImGuiTableFlags_ScrollY |
							  ImGuiTableFlags_RowBg |
							  ImGuiTableFlags_NoHostExtendX |
							  ImGuiTableFlags_BordersOuter |
							  ImGuiTableFlags_BordersV |
							  ImGuiTableFlags_Resizable |
							  ImGuiTableFlags_Reorderable |
							  ImGuiTableFlags_Hideable;

void MenuGui::render()
{
    ImGui::Begin("Menu GUI", nullptr, window_flags);

    if (ImGui::BeginMenuBar())
    {
	    if (ImGui::BeginMenu("File"))
	    {
            ImGui::MenuItem("Open", "Ctrl+O");
            ImGui::MenuItem("Save", "Ctrl+S");
            ImGui::MenuItem("Save as", "Ctrl+Shift+S");
            ImGui::MenuItem("Options", "Ctrl+Alt+S");
            ImGui::MenuItem("Close", "Alt+F4");

            ImGui::EndMenu();
	    }

        if (ImGui::BeginMenu("Tools"))
        {
            ImGui::MenuItem("Trim Data");
            ImGui::MenuItem("Filter Data");

            if (ImGui::BeginMenu("Plotting Tools"))
            {
				ImGui::MenuItem("Plot Data");

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    // Controls
    {
        ImGui::Begin("Controls");

        if (ImGui::Button("Load CSV"))
        {
            SPDLOG_INFO("Loading CSV file!");
        }

        ImGui::SameLine();

        if (ImGui::Button("Load data file"))
        {
            SPDLOG_INFO("Loading data file");
        }

        ImGui::Separator();

        if (ImGui::ArrowButton("LoadPageLeft", ImGuiDir_Left))
        {
            SPDLOG_INFO("Loading data page to the left");
        }

        ImGui::SameLine();

        if (ImGui::ArrowButton("LoadPageRight", ImGuiDir_Right))
        {
            SPDLOG_INFO("Loading data page to the right");
        }

        ImGui::End();
    }

    // Data view
    {
        ImGui::Begin("Data");

        if (ImGui::BeginTable("Data Table", 5, table_flags))
        {
            ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible.

            const std::vector<std::string> temp_headers = { "header1", "header2", "header3" }; // Some demo headers.

            // Loop over data headers here to determine table column names
            for (const auto& header : temp_headers)
            {
                ImGui::TableSetupColumn(header.c_str());
            }

            ImGui::TableHeadersRow();

            ImGuiListClipper clipper;
            clipper.Begin(10000);
            while (clipper.Step())
            {
	            for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
	            {
                    ImGui::TableNextRow();

                    for (int column = 0; column < temp_headers.size(); column++)
                    {
                        ImGui::TableSetColumnIndex(column);
                        ImGui::Text("%d-%d", row, column);
                    }
	            }
            }

            ImGui::EndTable();
        }

        ImGui::End();
    }

    ImGui::End();
}