#ifndef GUI_H
#define GUI_H

#include <iostream>

class Gui
{
public:
	Gui() = default;
	virtual ~Gui() { std::cout << "Destructing!\n"; }

	Gui(const Gui&) = default;
	Gui(Gui&&) noexcept = default;

	Gui& operator=(const Gui&) = default;
	Gui& operator=(Gui&&) noexcept = default;

	virtual void render() = 0;
};

#endif