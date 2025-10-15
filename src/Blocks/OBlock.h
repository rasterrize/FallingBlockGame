#pragma once

#include "Block.h"

namespace fbg
{
    class OBlock : public Block
    {
    public:
        OBlock(const glm::vec2& boardOrigin, const glm::ivec2& gridPos)
            : Block(boardOrigin, gridPos, pxl::Colour::AsVec4(pxl::ColourName::Yellow))
        {
            InitSegments();
        }

        virtual void InitSegments() override
        {
            // Clockwise from bottom left
            m_Segments[0] = Segment(m_BoardOrigin, k_UnitSize, m_GridPosition, m_Colour);

            m_Segments[1] = Segment(m_BoardOrigin, k_UnitSize, { m_GridPosition.x, m_GridPosition.y + 1 }, m_Colour);

            m_Segments[2] = Segment(m_BoardOrigin, k_UnitSize, { m_GridPosition.x + 1, m_GridPosition.y + 1 }, m_Colour);

            m_Segments[3] = Segment(m_BoardOrigin, k_UnitSize, { m_GridPosition.x + 1, m_GridPosition.y }, m_Colour);
        }
    };
}