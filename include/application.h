#ifndef APPLICATION_H
#define APPLICATION_H

#include "window.h"
#include "gui/gui_manager.h"

#include <memory>

class Application
{
public:
	Application();
	~Application();

	Application(const Application&) = delete;
	Application(Application&&) noexcept = delete;

	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) noexcept = delete;

	/**
	 * @brief Runs the main application.
	 */
	void run() const;

private:
	std::unique_ptr<Window> m_main_window_;
	std::unique_ptr<GuiManager> m_gui_manager_;

	/**
	 * @brief Sets up the application.
	 * @details This will set up GLFW.
	 */
	void setup();
};

#endif