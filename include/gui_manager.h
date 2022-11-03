#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "window.h"
#include "gui.h"

#include <vector>

class GuiManager
{
public:
    GuiManager(Window& target_window);;
    ~GuiManager() { shutdown(); }

    GuiManager(const GuiManager&) = delete;
    GuiManager(GuiManager&&) noexcept = delete;

    GuiManager& operator=(const GuiManager&) = delete;
    GuiManager& operator=(GuiManager&&) noexcept = delete;

    /**
     * @brief Renders each of the registered GUI targets.
     */
    void render() const;

    /**
     * @brief Show the Dear ImGui demo window (useful for development).
     */
    void show_demo_window() const;

    /**
     * @brief Registers a GUI to be rendered.
     */
    void register_gui(Gui* gui);

    /**
     * @brief Unregisters a GUI from the GUIs to be rendered.
     */
    void unregister_gui(Gui* gui);

    /**
     * @brief Clears all registered GUIs from rendering.
     */
    void clear();

    /*
     * TODO: Maybe could add a dark mode toggle here.
     */

private:
    Window m_target_window_;
    std::vector<Gui*> m_registered_guis_;

    /**
    * @brief Initialise the GuiManager.
    * @details Sets up the Dear ImGui context and prepares it for rendering.
    */
    void initialise() const;

    /**
     * @brief Clears up the GuiManager.
     */
    static void shutdown();

};

#endif