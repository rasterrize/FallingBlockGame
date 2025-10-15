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
            // Clockwise from bottom left
            m_Segments[0] = Segment(boardOrigin, k_UnitSize, gridPos, m_Colour);

            m_Segments[1] = Segment(boardOrigin, k_UnitSize, { gridPos.x, gridPos.y + 1 }, m_Colour);

            m_Segments[2] = Segment(boardOrigin, k_UnitSize, { gridPos.x + 1, gridPos.y + 1 }, m_Colour);

            m_Segments[3] = Segment(boardOrigin, k_UnitSize, { gridPos.x + 1, gridPos.y }, m_Colour);
        }
    };
}