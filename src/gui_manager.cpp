#include "gui_manager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

const std::string glsl_version = "#version 460";

GuiManager::GuiManager(Window& target_window)
    : m_target_window_{ std::move(target_window) }
{
    initialise();
}

void GuiManager::initialise() const
{
    // Set up Dear ImGui context.
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)90;

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


