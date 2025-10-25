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
        SetGridPosition(m_GridPosition + translate);
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

    void Block::UpdatePosition()
    {
        m_Position = { m_BoardOrigin.x + k_UnitSize * m_GridPosition.x, m_BoardOrigin.y + k_UnitSize * m_GridPosition.y, 0.2f };

        UpdateSegments();
    }

    void Block::UpdateSegments()
    {
        for (int segmentIndex = 0; segmentIndex < m_Segments.size(); segmentIndex++)
        {
            m_Segments[segmentIndex].SetGridPosition({ m_GridPosition.x + m_Rotations[m_RotationIndex][segmentIndex].x, m_GridPosition.y + m_Rotations[m_RotationIndex][segmentIndex].y });
        }
    }
}