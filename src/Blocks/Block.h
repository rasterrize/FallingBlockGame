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

        glm::ivec2 GetGridPosition() const { return m_GridPosition; }
        void SetGridPosition(const glm::ivec2& pos)
        {
            m_GridPosition = pos;
            UpdatePosition();
        }

        std::array<Segment, 4> GetSegments() const { return m_Segments; }

        void Translate(const glm::ivec2& translate);

        void MoveDown();
        void MoveLeft();
        void MoveRight();

        virtual void RotateLeft();
        // virtual void RotateRight();
        // virtual void Rotate180();

    protected:
        void UpdatePosition();

        virtual void InitSegments() = 0;

    protected:
        glm::vec3 m_Position;

        glm::ivec2 m_GridPosition;

        glm::vec4 m_Colour;

        std::array<Segment, 4> m_Segments = std::array<Segment, 4>();

        glm::vec2 m_BoardOrigin;
    };
}