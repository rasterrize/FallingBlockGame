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
            // Left
            m_Segments[0] = Segment(boardOrigin, k_UnitSize, { gridPos.x - 1, gridPos.y }, m_Colour);

            // Middle
            m_Segments[1] = Segment(boardOrigin, k_UnitSize, gridPos, m_Colour);

            // Right
            m_Segments[2] = Segment(boardOrigin, k_UnitSize, { gridPos.x + 1, gridPos.y }, m_Colour);

            // Top
            m_Segments[3] = Segment(boardOrigin, k_UnitSize, { gridPos.x, gridPos.y + 1 }, m_Colour);
        }
    };
}