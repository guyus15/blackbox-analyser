#ifndef MENU_GUI_H
#define MENU_GUI_H

#include "gui.h"

class MenuGui : public Gui
{
public:
    MenuGui() : Gui{} { }

    virtual void render() override;
};

#endif