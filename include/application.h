#ifndef APPLICATION_H
#define APPLICATION_H

#include "window.h"

#include <memory>

class Application
{
public:
	Application();
	~Application();

	Application(const Application&) = delete;
	Application(Application&&) noexcept = default;

	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) noexcept = default;

	void run() const;

private:
	std::unique_ptr<Window> m_main_window_;

	void setup();
};

#endif