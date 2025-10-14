#include "Segment.h"

namespace fbg
{
    Segment::Segment()
        : m_GridPosition(glm::ivec2(0)), m_UnitSize(0.0f)
    {
    }

    Segment::Segment(const glm::vec2& boardOrigin, float unitSize, const glm::ivec2& gridPos, const glm::vec4& colour)
        : m_GridPosition(gridPos), m_UnitSize(unitSize)
    {
        m_DrawQuad = {};
        // TODO: z should be the block's Z
        m_DrawQuad.Position = { boardOrigin.x + unitSize * gridPos.x, boardOrigin.y + unitSize * gridPos.y, 0.2f };
        m_DrawQuad.Colour = colour;
        m_DrawQuad.Size = glm::vec2(m_UnitSize);
        m_DrawQuad.Origin = pxl::Origin2D::BottomLeft;
    }

    void Segment::Translate(const glm::ivec2& translate)
    {
        m_GridPosition += translate;

        m_DrawQuad.Position.x += translate.x * m_UnitSize;
        m_DrawQuad.Position.y += translate.y * m_UnitSize;
    }
}