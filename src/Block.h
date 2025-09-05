#pragma once

#include <pxl/pxl.h>

#include <glm/glm.hpp>

namespace fbg
{
    class Block
    {
    public:
        Block(const glm::vec3& pos)
            : m_Position(pos) {}

        void Draw();

        glm::vec3 GetPosition() { return m_Position; }
        void SetPosition(const glm::vec3& pos) { m_Position = pos; }

        void Translate(const glm::vec3& translate)
        {
            m_Position += translate;
            TranslateQuads(translate);
        }

        void TranslateQuads(const glm::vec3& translate)
        {
            for (auto& quad : m_Quads)
            {
                quad.Position += translate;
            }
        }
    protected:
        glm::vec3 m_Position;

        std::array<pxl::Quad, 4> m_Quads;

        const float k_UnitSize = 35.0f;
    };
}