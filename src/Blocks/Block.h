#pragma once

#include <pxl/pxl.h>

#include <glm/glm.hpp>

#include "../Segment.h"

namespace fbg
{
    constexpr float k_UnitSize = 35.0f;

    class Block
    {
    public:
        Block(const glm::vec2& boardOrigin, const glm::ivec2& gridPos, const glm::vec4& colour);

        void Draw();

        // WARNING: does not update grid position, as they won't match
        // void SetPosition(const glm::vec3& pos) { m_Position = pos; }

        glm::ivec2 GetGridPosition() const { return m_GridPosition; }
        void SetGridPosition(const glm::ivec2& pos)
        {
            m_GridPosition = pos;
            UpdatePosition();
        }

        std::array<Segment, 4> GetSegments() const { return m_Segments; }

        uint32_t GetRotationIndex() const { return m_RotationIndex; }
        void SetRotationIndex(uint32_t index) { m_RotationIndex = index; }

        void SetColour(const glm::vec4& colour)
        {
            m_Colour = colour;

            for (auto& segment : m_Segments)
                segment.SetColour(colour);
        }

        void Translate(const glm::ivec2& translate);

        void MoveDown();
        void MoveLeft();
        void MoveRight();

        // NOTE: 0 = up 1 = right 2 = down 3 = left
        void RotateLeft()
        {
            m_RotationIndex = (m_RotationIndex - 1) % 4;
            UpdateSegments();
        }
        void RotateRight()
        {
            m_RotationIndex = (m_RotationIndex + 1) % 4;
            UpdateSegments();
        }

        void Rotate180()
        {
            m_RotationIndex = (m_RotationIndex + 2) % 4;
            UpdateSegments();
        }

    protected:
        void UpdatePosition();
        void UpdateSegments();

        virtual void InitSegments() {}

    protected:
        glm::vec3 m_Position;

        glm::ivec2 m_GridPosition;

        // glm::ivec2 m_OriginGridPosition;

        glm::vec4 m_Colour = glm::vec4(1.0f);

        uint32_t m_RotationIndex = 0;

        std::array<std::array<glm::ivec2, 4>, 4> m_Rotations = std::array<std::array<glm::ivec2, 4>, 4>();

        std::array<Segment, 4> m_Segments = std::array<Segment, 4>();

        glm::vec2 m_BoardOrigin;
    };
}