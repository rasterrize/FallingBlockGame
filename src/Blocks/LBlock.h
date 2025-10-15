#pragma once

#include "Block.h"

namespace fbg
{
    class LBlock : public Block
    {
    public:
        LBlock(const glm::vec2& boardOrigin, const glm::ivec2& gridPos)
            : Block(boardOrigin, gridPos, glm::vec4(252.0f / 255.0f, 136.0f / 255.0f, 3 / 255.0f, 1.0f))
        {
            InitSegments();
        }

        virtual void InitSegments() override
        {
            // Top down
            m_Segments[0] = Segment(m_BoardOrigin, k_UnitSize, { m_GridPosition.x, m_GridPosition.y + 1 }, m_Colour);

            m_Segments[1] = Segment(m_BoardOrigin, k_UnitSize, m_GridPosition, m_Colour);

            m_Segments[2] = Segment(m_BoardOrigin, k_UnitSize, { m_GridPosition.x, m_GridPosition.y - 1 }, m_Colour);

            m_Segments[3] = Segment(m_BoardOrigin, k_UnitSize, { m_GridPosition.x + 1, m_GridPosition.y - 1 }, m_Colour);
        }
    };
}