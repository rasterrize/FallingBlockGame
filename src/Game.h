#pragma once

#include <pxl/pxl.h>

#include "Blocks/Block.h"

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
        void StartNewGame();

        std::unique_ptr<Block> GenerateRandomBlock(int x, int y);

        bool IsEmptyBelow(const glm::ivec2& gridPos);
        bool IsEmptyLeft(const glm::ivec2& gridPos);
        bool IsEmptyRight(const glm::ivec2& gridPos);

        void PlacePlayerBlock();

        void CheckBoundsAndMove();

        void NextPlayerBlock();

        bool CanPlacePlayerBlock();

        void SetupHologram();

    private:
        std::shared_ptr<pxl::Texture> m_BoardTexture;
        std::shared_ptr<pxl::Texture> m_GridTexture;

        const float k_UnitSize = 35.0f;
        const glm::vec2 k_BlockBoardOrigin = { 337.0f, 34.0f };
        const float k_DefaultFallTime = 0.4f;

        std::array<std::array<std::optional<Segment>, 10>, 20> m_PlacedSegs;

        // Time it takes for a block to fall to the next line
        float m_FallTimeSetting = k_DefaultFallTime;
        float m_CurrentFallTime = 0.0f;
        float m_ElapsedTime = 0.0f;

        float m_SoftDropSpeed = 3.0f;

        bool m_PlayerCanHold = true;

        std::unique_ptr<Block> m_PlayerBlock;
        std::unique_ptr<Block> m_HeldBlock;

        std::array<Segment, 4> m_HologramSegments;

        std::vector<std::unique_ptr<Block>> m_BlockBag;
    };
}