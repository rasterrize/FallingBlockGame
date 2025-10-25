#pragma once

#include "Block.h"

namespace fbg
{
    class IBlock : public Block
    {
    public:
        IBlock(const glm::vec2& boardOrigin, const glm::ivec2& gridPos)
            : Block(boardOrigin, gridPos, glm::vec4(0.0f / 255.0f, 187.0f / 255.0f, 255.0f / 255.0f, 1.0f))
        {
            // Init rotation positions

            // up
            m_Rotations[0][0] = { -2, 0 };
            m_Rotations[0][1] = { -1, 0 };
            m_Rotations[0][2] = { 0, 0 };
            m_Rotations[0][3] = { 1, 0 };

            // right
            m_Rotations[1][0] = { 0, 1 };
            m_Rotations[1][1] = { 0, 0 };
            m_Rotations[1][2] = { 0, -1 };
            m_Rotations[1][3] = { 0, -2 };

            // down
            m_Rotations[2][0] = { 1, -1 };
            m_Rotations[2][1] = { 0, -1 };
            m_Rotations[2][2] = { -1, -1 };
            m_Rotations[2][3] = { -2, -1 };

            // left
            m_Rotations[3][0] = { -1, 2 };
            m_Rotations[3][1] = { -1, 1 };
            m_Rotations[3][2] = { -1, 0 };
            m_Rotations[3][3] = { -1, -1 };

            InitSegments();
        }

        virtual void InitSegments() override
        {
            // Top down
            // for (int i = 0; i < m_Segments.size(); i++)
            // {
            //     m_Segments[i] = Segment(m_BoardOrigin, k_UnitSize, m_GridPosition + m_Rotations[0][i], m_Colour);
            // }

            m_Segments[0] = Segment(m_BoardOrigin, k_UnitSize, { m_GridPosition.x - 2, m_GridPosition.y }, m_Colour);

            m_Segments[1] = Segment(m_BoardOrigin, k_UnitSize, { m_GridPosition.x - 1, m_GridPosition.y }, m_Colour);

            m_Segments[2] = Segment(m_BoardOrigin, k_UnitSize, m_GridPosition, m_Colour);

            m_Segments[3] = Segment(m_BoardOrigin, k_UnitSize, { m_GridPosition.x + 1, m_GridPosition.y }, m_Colour);
        }
    };
}