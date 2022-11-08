#include "gui/menu_gui.h"

#include "data_loader.h"

#include "imgui.h"
#include "spdlog/spdlog.h"
#include "tinyfiledialogs.h"

ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
                                ImGuiWindowFlags_MenuBar |
                                ImGuiWindowFlags_NoCollapse |
                                ImGuiWindowFlags_NoMove |
                                ImGuiWindowFlags_NoSavedSettings |
                                ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoBringToFrontOnFocus;

ImGuiTableFlags table_flags = ImGuiTableFlags_ScrollX |
                              ImGuiTableFlags_ScrollY |
                              ImGuiTableFlags_RowBg |
                              ImGuiTableFlags_NoHostExtendX |
                              ImGuiTableFlags_BordersOuter |
                              ImGuiTableFlags_BordersV |
                              ImGuiTableFlags_Resizable |
                              ImGuiTableFlags_Reorderable |
                              ImGuiTableFlags_Hideable;

ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

void MenuGui::render()
{
    ImGui::Begin("Menu GUI", nullptr, window_flags);

    const ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);

    ImGui::DockSpace(dockspace_id, ImVec2(0, 0), dockspace_flags);

    // Main menu bar
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open", "Ctrl+O"))
            {
                handle_open();
            }

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

        ImGui::EndMainMenuBar();
    }

    // Controls
    {
        ImGui::Begin("Controls");

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

        if (m_target_data_.get_headers().empty())
        {
            ImGui::Text("No log file has been opened.");
        }
        else
        {
            const int num_columns = static_cast<int>(m_target_data_.get_headers().size());

            if (ImGui::BeginTable("Data Table", num_columns, table_flags))
            {
                ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible.

                const std::vector<std::string> temp_headers = { "header1", "header2", "header3" }; // Some demo headers.

                // Loop over data headers here to determine table column names
                for (const auto& header : m_target_data_.get_headers())
                {
                    ImGui::TableSetupColumn(header.c_str());
                }

                ImGui::TableHeadersRow();

                ImGuiListClipper clipper;
                clipper.Begin(static_cast<int>(m_target_data_.size()) - 1);
                while (clipper.Step())
                {
                    for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
                    {
                        ImGui::TableNextRow();


                        for (int column = 0; column < static_cast<int>(m_target_data_.get_headers().size()); column++)
                        {
                            LogRecord current_record = m_target_data_[row];

                            ImGui::TableSetColumnIndex(column);

                            // Retrieve the relevant field from the log record struct.
                            ImGui::Text("%s", (&current_record.datetime)[column].c_str());

                        }
                    }
                }

                ImGui::EndTable();
            }
        }

        ImGui::End();
    }

    ImGui::End();
}

void MenuGui::handle_open()
{
    SPDLOG_INFO("Handling open operation.");

    open_file_dialog();

    // TODO: There needs to be some logic here to determine what type of log file the user has entered, whether it's in CSV format, CSV-verbose
    // format or if it's serialised. For now we'll assume everything is a CsvSource.
    constexpr DataLoader<CsvSource> csv_loader{};
    
    m_target_data_ = csv_loader.load(m_filepath_);
}

void MenuGui::open_file_dialog()
{
    const char* filter_patterns[2] = { "*.txt", "*.csv" };

    const char* selection = tinyfd_openFileDialog(
        "Select file",
        "C:\\",
        2,
        filter_patterns,
        nullptr,
        0
    );

    // TODO: some error handling here - closing open file dialog without selecting path causes exception.
    m_filepath_ = selection;
}
