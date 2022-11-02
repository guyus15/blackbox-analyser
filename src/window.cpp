#include "window.h"

#include <utility>

#include "spdlog/spdlog.h"

Window::Window(std::string title, const GLsizei width, const GLsizei height, const WindowMode mode)
	: m_window{ nullptr }
{
	WindowProperties properties;

	properties.title = std::move(title);
	properties.dimensions = { width, height };
	properties.mode = mode;

	initialise_window(properties);
}

Window::~Window()
{
	destroy_window();
}

void Window::make_context_current() const
{
	glfwMakeContextCurrent(m_window);
}

void Window::focus_window() const
{
	glfwFocusWindow(m_window);
}

void Window::maximise_window() const
{
	glfwMaximizeWindow(m_window);
}

void Window::restore_window() const
{
	glfwRestoreWindow(m_window);
}

void Window::close_window() const
{
	glfwSetWindowShouldClose(m_window, true);
}

bool Window::should_close() const
{
	return glfwWindowShouldClose(m_window);
}

GLFWwindow* Window::get_window_ptr() const
{
	return m_window;
}

WindowDimensions Window::get_window_dimensions() const
{
	int width = 0, height = 0;
	glfwGetWindowSize(m_window, &width, &height);

	WindowDimensions dimensions{};
	dimensions.width = width;
	dimensions.height = height;

	return dimensions;
}

void Window::initialise_window(const WindowProperties& properties)
{
	m_window = glfwCreateWindow(
		static_cast<int>(properties.dimensions.width),
		static_cast<int>(properties.dimensions.height),
		properties.title.c_str(),
		properties.mode == WindowMode::FULLSCREEN ? glfwGetPrimaryMonitor() : nullptr,
		nullptr);

	if (m_window == nullptr)
	{
		spdlog::error("Failed to create GLFW window.");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
}

void Window::destroy_window() const
{
	glfwDestroyWindow(m_window);
}
