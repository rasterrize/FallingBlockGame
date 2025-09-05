#pragma once

#include <pxl/pxl.h>

namespace fbg
{
    class Game : public pxl::Application
    {
    public:
        Game();
        ~Game();

        void OnUpdate(float dt);
        void OnRender();
        void OnGUIRender();
        void OnClose();

    private:
        std::shared_ptr<pxl::Texture> m_BoardTexture;
        std::shared_ptr<pxl::Texture> m_GridTexture;

        const float k_BlockSize = 35.0f;
        const glm::vec2 k_BlockBoardOrigin = { 387.0f, 34.0f };
    };
}