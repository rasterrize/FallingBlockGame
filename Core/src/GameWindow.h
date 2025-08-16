#include <GLFW/glfw3.h>

#include <string>
#include <vector>

namespace fbg
{
    struct WindowConfig
    {
        uint32_t Width = 1280;
        uint32_t Height = 720;
        std::string Title = "Window Title";
    };

    class GameWindow
    {
    public:
        GameWindow()
            : GameWindow(WindowConfig())
        {
        }

        GameWindow(const WindowConfig& config);
        ~GameWindow();

        GLFWwindow* GetHandle() { return m_Handle; }

        bool ShouldClose() { return glfwWindowShouldClose(m_Handle); }

        void PollEvents();
        void Present();

        void Close();

    private:
        GLFWwindow* m_Handle = nullptr;

        static std::vector<GLFWwindow*> s_WindowRegistry;
    };
}