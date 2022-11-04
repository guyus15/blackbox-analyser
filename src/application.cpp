#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "application.h"
#include "window.h"

#include "gui/gui_manager.h"
#include "gui/menu_gui.h"

#include "spdlog/spdlog.h"

#include <cstdlib>

static void error_callback(int, const char*);

Application::Application()
    : m_main_window_{ nullptr }
{
    setup();
}

Application::~Application()
{
    m_main_window_.reset();
    m_gui_manager_.reset();

    glfwTerminate();
}

void Application::run() const
{
    while (!m_main_window_->should_close())
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_gui_manager_->render();

        glfwSwapBuffers(m_main_window_->get_window_ptr());
        glfwPollEvents();
    }
}

void Application::setup()
{
    // Initialising GLFW
    if (!glfwInit())
    {
        SPDLOG_ERROR("Failed to initialise GLFW.");
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_main_window_ = std::make_unique<Window>("Blackbox: Analyser", 1280, 720, WindowMode::WINDOWED);
    m_main_window_->make_context_current();

    // Create GUI targets.
    auto* menu_gui = new MenuGui();

    m_gui_manager_ = std::make_unique<GuiManager>(*m_main_window_);
    m_gui_manager_->register_gui(menu_gui);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        SPDLOG_ERROR("Failed to initialise GLAD.");
        exit(EXIT_FAILURE);
    }

    const auto [width, height] = m_main_window_->get_window_dimensions();

    glViewport(0, 0, width, height);
}

static void error_callback(int error_code, const char* err_str)
{
    SPDLOG_ERROR("GLFW Error: {0}", err_str);
}