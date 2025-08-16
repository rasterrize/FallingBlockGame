#include "GameWindow.h"

#include <print>

namespace fbg
{
    GameWindow::GameWindow(const WindowConfig& config)
    {
        if (!glfwInit())
            std::print("GLFW initialized");

        // We are using OpenGL 4.6
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

        m_Handle = glfwCreateWindow(config.Width, config.Height, config.Title.c_str(), nullptr, nullptr);
    }

    GameWindow::~GameWindow()
    {
        // Force close window
        Close();

        // NOTE: Usually this should only be called once all windows are closed,
        // but this game will only ever use 1 window so it's fine
        glfwTerminate();
    }

    void GameWindow::PollEvents()
    {
        glfwPollEvents();
    }

    void GameWindow::Present()
    {
        glfwSwapBuffers(m_Handle);
    }

    void GameWindow::Close()
    {
        if (m_Handle)
            glfwDestroyWindow(m_Handle);
    }
}
