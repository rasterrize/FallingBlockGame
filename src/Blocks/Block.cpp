#include "Block.h"

namespace fbg
{
    Block::Block(const glm::vec2& boardOrigin, const glm::ivec2& gridPos, const glm::vec4& colour)
        : m_GridPosition(gridPos), m_Colour(colour), m_BoardOrigin(boardOrigin)
    {
        UpdatePosition();
    }

    void Block::Draw()
    {
        for (const auto& segment : m_Segments)
        {
            pxl::Renderer::AddQuad(segment.GetDrawQuad());
        }
    }

    void Block::Translate(const glm::ivec2& translate)
    {
        m_GridPosition += translate;

        m_Position.x += translate.x * k_UnitSize;
        m_Position.y += translate.y * k_UnitSize;

        for (auto& segment : m_Segments)
            segment.Translate(translate);
    }

    void Block::MoveDown()
    {
        Translate({ 0, -1 });
    }

    void Block::MoveLeft()
    {
        Translate({ -1, 0 });
    }

    void Block::MoveRight()
    {
        Translate({ 1, 0 });
    }

    void Block::RotateLeft()
    {
        // for (auto& segment : m_Segments)
        // {
        //     segment.SetGrid
        // }
    }

    void Block::UpdatePosition()
    {
        m_Position = { m_BoardOrigin.x + k_UnitSize * m_GridPosition.x, m_BoardOrigin.y + k_UnitSize * m_GridPosition.y, 0.2f };
    }
}