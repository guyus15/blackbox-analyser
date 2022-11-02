#ifndef WINDOW_H
#define WINDOW_H

#include "GLFW/glfw3.h"

#include <string>

/**
 * @brief The modes that the window can be in.
 */
enum class WindowMode
{
	WINDOWED,
	FULLSCREEN
};

const std::string DEFAULT_TITLE = "Untitled";
constexpr unsigned int DEFAULT_WIDTH = 1280;
constexpr unsigned int DEFAULT_HEIGHT = 720;
constexpr WindowMode DEFAULT_WINDOW_MODE = WindowMode::WINDOWED;


/**
 * @brief A struct representing the width and height of a window.
 */
struct WindowDimensions
{
	GLsizei width, height;
};

/**
 * @brief A struct containing window properties.
 */
struct WindowProperties
{
	std::string title;
	WindowDimensions dimensions{};
	WindowMode mode = WindowMode::WINDOWED;
};

class Window
{
public:
	explicit Window(std::string title = DEFAULT_TITLE, GLsizei width = DEFAULT_WIDTH, GLsizei height = DEFAULT_HEIGHT, WindowMode mode = WindowMode::WINDOWED);
	~Window();

	Window(const Window&) = delete;
	Window(Window&&) noexcept = default;

	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) noexcept = default;

	/**
	 * @brief Sets the current GLFW context to be this window.
	 */
	void make_context_current() const;

	/**
	 * @brief Give this window focus and bring it to the front.
	 */
	void focus_window() const;

	/**
	 * @brief Maximise this window.
	 */
	void maximise_window() const;

	/**
	 * @brief Restore this window.
	 */
	void restore_window() const;

	/**
	 * @brief Set the window close flag.
	 */
	void close_window() const;

	/**
	 * @brief Returns whether or not the window should be closed.
	 * @return true If the window should close.
	 * @return false If the window should not close.
	 */
	[[nodiscard]] bool should_close() const;

	/**
	 * @brief Gets the GLFW window pointer.
	 * @return The GLFW window pointer.
	 */
	[[nodiscard]] GLFWwindow* get_window_ptr() const;

	WindowDimensions get_window_dimensions() const;

private:
	GLFWwindow* m_window;

	/**
	 * @brief Creates a GLFW window from a set of window properties.
	 */
	void initialise_window(const WindowProperties& properties);

	/**
	 * @brief Destroys this window.
	 */
	void destroy_window() const;
};

#endif