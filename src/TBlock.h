#pragma once

#include "Block.h"

namespace fbg
{
    class TBlock : public Block
    {
    public:
        TBlock(const glm::vec3 pos)
            : Block(pos)
        {
            pxl::Quad base = {
                .Size = glm::vec2(k_UnitSize),
                .Colour = pxl::Colour::AsVec4(pxl::ColourName::Pink),
                .Origin = pxl::Origin2D::BottomLeft,
            };

            pxl::Quad left = base;
            left.Position = { m_Position.x - k_UnitSize, m_Position.y, 0.2f };
            m_Quads[0] = left;

            pxl::Quad middle = base;
            middle.Position = { m_Position.x, m_Position.y, 0.2f };
            m_Quads[1] = middle;

            pxl::Quad right = base;
            right.Position = { m_Position.x + k_UnitSize, m_Position.y, 0.2f };
            m_Quads[2] = right;

            pxl::Quad top = base;
            top.Position = { m_Position.x, m_Position.y + k_UnitSize, 0.2f };
            m_Quads[3] = top;
        }
    };
}