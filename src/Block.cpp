#include "Block.h"

namespace fbg
{
    void Block::Draw()
    {
        for (const auto& quad : m_Quads)
        {
            pxl::Renderer::AddQuad(quad);
        }
    }
}