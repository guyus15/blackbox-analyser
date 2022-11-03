#include "menu_gui.h"

#include "imgui.h"

void MenuGui::render()
{
    ImGui::Begin("Menu Gui");

    ImGui::Text("This is some useful text!");

    ImGui::End();
}