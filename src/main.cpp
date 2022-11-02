#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"

#include "window.h"

#include <cstdlib>

int main()
{
#if defined(BX_LOG_DEBUG)
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::err);
#endif

    // Initialising GLFW
    if (!glfwInit())
    {
        spdlog::error("Failed to initialise GLFW.");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const Window window{"Blackbox: Analyser", 1280, 720, WindowMode::WINDOWED};
    window.make_context_current();

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        spdlog::error("Failed to initialise GLAD.");
        exit(EXIT_FAILURE);
    }

    const auto [width, height] = window.get_window_dimensions();
    glViewport(0, 0, width, height);

    while (!window.should_close())
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window.get_window_ptr());
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}