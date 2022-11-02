#include "window.h"

#include <utility>

#include "spdlog/spdlog.h"

Window::Window(std::string title, const GLsizei width, const GLsizei height, const WindowMode mode)
	: m_window_{ nullptr }
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
	glfwMakeContextCurrent(m_window_);
}

void Window::focus_window() const
{
	glfwFocusWindow(m_window_);
}

void Window::maximise_window() const
{
	glfwMaximizeWindow(m_window_);
}

void Window::restore_window() const
{
	glfwRestoreWindow(m_window_);
}

void Window::close_window() const
{
	glfwSetWindowShouldClose(m_window_, true);
}

bool Window::should_close() const
{
	return glfwWindowShouldClose(m_window_);
}

GLFWwindow* Window::get_window_ptr() const
{
	return m_window_;
}

WindowDimensions Window::get_window_dimensions() const
{
	int width = 0, height = 0;
	glfwGetWindowSize(m_window_, &width, &height);

	WindowDimensions dimensions{};
	dimensions.width = width;
	dimensions.height = height;

	return dimensions;
}

void Window::initialise_window(const WindowProperties& properties)
{
	m_window_ = glfwCreateWindow(
		properties.dimensions.width,
		properties.dimensions.height,
		properties.title.c_str(),
		properties.mode == WindowMode::FULLSCREEN ? glfwGetPrimaryMonitor() : nullptr,
		nullptr);

	if (m_window_ == nullptr)
	{
		SPDLOG_ERROR("Failed to create GLFW window.");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
}

void Window::destroy_window() const
{
	glfwDestroyWindow(m_window_);
}
