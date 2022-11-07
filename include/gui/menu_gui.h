#ifndef MENU_GUI_H
#define MENU_GUI_H

#include "gui.h"
#include "common_data.h"

class MenuGui : public Gui
{
public:
    MenuGui() : Gui{} { }

    virtual void render() override;

private:
    std::string m_filepath_;
    CommonData m_target_data_;

    /**
     * @brief Handles the open operation.
     */
    void handle_open();

    /**
     * @brief A dialogue which opens when the user is trying to open a log file.
     */
    void open_file_dialog();
};

#endif