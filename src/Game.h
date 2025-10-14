#pragma once

#include <pxl/pxl.h>

#include "Block.h"

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
        void StartGame();

        bool SpawnNewBlock(int x, int y);

        bool CheckBelowSegment(const glm::ivec2& gridPos);
        bool CheckLeftSegment(const glm::ivec2& gridPos);
        bool CheckRightSegment(const glm::ivec2& gridPos);

        void PlacePlayerBlock();

    private:
        std::shared_ptr<pxl::Texture> m_BoardTexture;
        std::shared_ptr<pxl::Texture> m_GridTexture;

        const float k_UnitSize = 35.0f;
        const glm::vec2 k_BlockBoardOrigin = { 337.0f, 34.0f };
        const float k_BoardBottomY = 34.0f;

        std::array<std::array<std::optional<Segment>, 20>, 10> m_Grid;

        // Time it takes for a block to fall to the next line
        float m_FallTime = 0.4f;
        float m_ElapsedTime = 0.0f;

        // TEMP
        std::unique_ptr<Block> playerBlock;
    };
}