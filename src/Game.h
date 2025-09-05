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
    };
}