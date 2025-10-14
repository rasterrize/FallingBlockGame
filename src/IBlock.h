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
            // Top down
            m_Segments[0] = Segment(boardOrigin, k_UnitSize, { gridPos.x, gridPos.y + 1 }, m_Colour);

            m_Segments[1] = Segment(boardOrigin, k_UnitSize, gridPos, m_Colour);

            m_Segments[2] = Segment(boardOrigin, k_UnitSize, { gridPos.x, gridPos.y - 1}, m_Colour);
            
            m_Segments[3] = Segment(boardOrigin, k_UnitSize, { gridPos.x, gridPos.y - 2 }, m_Colour);
        }
    };
}