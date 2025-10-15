#pragma once

#include "Block.h"

namespace fbg
{
    class TBlock : public Block
    {
    public:
        TBlock(const glm::vec2& boardOrigin, const glm::ivec2& gridPos)
            : Block(boardOrigin, gridPos, glm::vec4(173.0f / 255.0f, 66 / 255.0f, 245 / 255.0f, 1.0f))
        {
            InitSegments();
        }

        virtual void InitSegments() override
        {
            // Left
            m_Segments[0] = Segment(m_BoardOrigin, k_UnitSize, { m_GridPosition.x - 1, m_GridPosition.y }, m_Colour);

            // Middle
            m_Segments[1] = Segment(m_BoardOrigin, k_UnitSize, m_GridPosition, m_Colour);

            // Right
            m_Segments[2] = Segment(m_BoardOrigin, k_UnitSize, { m_GridPosition.x + 1, m_GridPosition.y }, m_Colour);

            // Top
            m_Segments[3] = Segment(m_BoardOrigin, k_UnitSize, { m_GridPosition.x, m_GridPosition.y + 1 }, m_Colour);
        }
    };
}