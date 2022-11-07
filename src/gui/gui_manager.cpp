#include "gui/gui_manager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

const std::string glsl_version = "#version 460";

GuiManager::GuiManager(Window& target_window)
    : m_target_window_{ target_window }
{
    initialise();
}

void GuiManager::initialise() const
{
    // Set up Dear ImGui context.
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    const ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Set the Dear ImGui style.
    ImGui::StyleColorsDark();

    // Set up platform/renderer backends.
    ImGui_ImplGlfw_InitForOpenGL(m_target_window_.get_window_ptr(), true);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());
}

void GuiManager::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GuiManager::render() const
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

#ifdef IMGUI_HAS_VIEWPORT
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetWorkPos());
    ImGui::SetNextWindowSize(viewport->GetWorkSize());
    ImGui::SetNextWindowViewport(viewport->ID);
#else
    const auto [width, height] = m_target_window_.get_window_dimensions();

    ImGui::SetNextWindowPos(ImVec2{ 0.0f, 0.0f });
    ImGui::SetNextWindowSize(ImVec2{static_cast<float>(width), static_cast<float>(height)});
#endif

    for (const auto& gui : m_registered_guis_)
    {
        gui->render();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiManager::register_gui(Gui* gui)
{
    m_registered_guis_.emplace_back(gui);
}

void GuiManager::unregister_gui(Gui* gui)
{
    // TODO: To be implemented. Probably need some sort of UUID for the Gui objects.
    return;
}

void GuiManager::clear()
{
    for (const auto& gui : m_registered_guis_)
    {
        delete gui;
    }

    m_registered_guis_.clear();
}


