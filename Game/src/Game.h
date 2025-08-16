#include <memory>

#include "GameWindow.h"

namespace fbg
{
    class Game
    {
    public:
        Game();

        void Run();

    private:
        bool m_RunGameLoop = true;

        std::unique_ptr<GameWindow> m_Window;
    };
}