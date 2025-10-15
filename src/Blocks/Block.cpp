#include "Block.h"

namespace fbg
{
    Block::Block(const glm::vec2& boardOrigin, const glm::ivec2& gridPos, const glm::vec4& colour)
        : m_Position({ boardOrigin.x + k_UnitSize * gridPos.x, boardOrigin.y + k_UnitSize * gridPos.y, 0.2f }), m_GridPosition(gridPos), m_Colour(colour)
    {
    }

    void Block::Draw()
    {
        for (const auto& segment : m_Segments)
        {
            pxl::Renderer::AddQuad(segment.GetDrawQuad());
        }
    }

    void Block::Translate(const glm::ivec2& translate)
    {
        m_GridPosition += translate;

        m_Position.x += translate.x * k_UnitSize;
        m_Position.y += translate.y * k_UnitSize;

        for (auto& segment : m_Segments)
            segment.Translate(translate);
    }

    void Block::MoveDown()
    {
        Translate({ 0, -1 });
    }

    void Block::MoveLeft()
    {
        Translate({ -1, 0 });
    }

    void Block::MoveRight()
    {
        Translate({ 1, 0 });
    }
}