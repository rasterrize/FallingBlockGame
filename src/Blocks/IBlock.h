#pragma once

#include "Block.h"

namespace fbg
{
    class IBlock : public Block
    {
    public:
        IBlock(const glm::vec2& boardOrigin, const glm::ivec2& gridPos)
            : Block(boardOrigin, gridPos, glm::vec4(0.0f / 255.0f, 187 / 255.0f, 255 / 255.0f, 1.0f))
        {
            InitSegments();
        }

        virtual void InitSegments() override
        {
            // Top down
            m_Segments[0] = Segment(m_BoardOrigin, k_UnitSize, { m_GridPosition.x, m_GridPosition.y + 1 }, m_Colour);

            m_Segments[1] = Segment(m_BoardOrigin, k_UnitSize, m_GridPosition, m_Colour);

            m_Segments[2] = Segment(m_BoardOrigin, k_UnitSize, { m_GridPosition.x, m_GridPosition.y - 1 }, m_Colour);

            m_Segments[3] = Segment(m_BoardOrigin, k_UnitSize, { m_GridPosition.x, m_GridPosition.y - 2 }, m_Colour);
        }
    };
}