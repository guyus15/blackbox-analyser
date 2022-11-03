#ifndef DEMO_GUI_H
#define DEMO_GUI_H

#include "gui.h"

class DemoGui : public Gui
{
public:
    DemoGui() : Gui{} { }

    virtual void render() override;
};

#endif