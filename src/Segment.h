#include <pxl/pxl.h>

#include <glm/glm.hpp>

namespace fbg
{
    // A segment of a falling block
    class Segment
    {
    public:
        Segment();
        Segment(const glm::vec2& boardOrigin, float unitSize, const glm::ivec2& gridPos, const glm::vec4& colour);

        glm::ivec2 GetGridPosition() const { return m_GridPosition; }
        void SetGridPosition(const glm::ivec2& pos) { m_GridPosition = pos; }

        pxl::Quad GetDrawQuad() const { return m_DrawQuad; }

        void Translate(const glm::ivec2& translate);

        void SetColour(const glm::vec4& colour) { m_DrawQuad.Colour = colour; }

    private:
        glm::ivec2 m_GridPosition;

        pxl::Quad m_DrawQuad;

        float m_UnitSize;
    };
}