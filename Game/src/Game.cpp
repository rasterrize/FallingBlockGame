#include "Game.h"

namespace fbg
{
    Game::Game()
    {
        m_Window = std::make_unique<GameWindow>();
    }

    void Game::Run()
    {
        while (m_RunGameLoop && !m_Window->ShouldClose())
        {
            m_Window->PollEvents();
        }
    }
}