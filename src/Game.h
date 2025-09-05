#pragma once

#include <pxl/pxl.h>

#include "TBlock.h"

namespace fbg
{
    class Game : public pxl::Application
    {
    public:
        Game();
        ~Game();

        void OnUpdate(float dt);
        void OnRender();
        void OnGUIRender();
        void OnClose();

    private:
        std::shared_ptr<pxl::Texture> m_BoardTexture;
        std::shared_ptr<pxl::Texture> m_GridTexture;

        const float k_UnitSize = 35.0f;
        const glm::vec2 k_BlockBoardOrigin = { 387.0f, 34.0f };
        const float k_BoardBottomY = 34.0f;

        uint32_t m_Grid[20][10];

        // Time it takes for a block to fall to the next line
        float m_FallTime = 0.8f;
        float m_ElapsedTime = 0.0f;

        // TEMP
        std::unique_ptr<TBlock> block;
    };
}