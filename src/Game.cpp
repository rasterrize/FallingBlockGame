#include "Game.h"

namespace fbg
{
    Game::Game()
    {
        pxl::WindowSpecs specs = {
            .Title = "Falling Block Game",
            .Size = { 1024, 768 },
            .RendererAPI = pxl::RendererAPIType::OpenGL,
        };
        auto window = pxl::Window::Create(specs);

        pxl::Renderer::Init(window);

        pxl::OrthographicSettings ortho = {};
        ortho.AspectRatio = window->GetAspectRatio();
        ortho.NearClip = -1.0f;
        ortho.FarClip = 1.0f;
        ortho.Bottom = 0.0f;
        ortho.Top = 768.0f;
        ortho.Left = 0.0f;
        ortho.Right = 1024.0f;
        ortho.UseAspectRatio = false;
        ortho.Zoom = 1.0f;

        auto camera = pxl::Camera::CreateOrthographic(ortho);

        pxl::Renderer::SetCameraAll(camera);

        auto boardImage = pxl::FileSystem::LoadImageFile("assets/textures/board.png");
        auto gridImage = pxl::FileSystem::LoadImageFile("assets/textures/grid.png");

        pxl::TextureSpecs textureSpecs = {};
        textureSpecs.Filter = pxl::SampleFilter::Linear;
        textureSpecs.Type = pxl::TextureType::Tex2D;
        textureSpecs.WrapMode = pxl::TextureWrap::ClampToEdge;

        m_BoardTexture = pxl::Texture::Create(boardImage, textureSpecs);
        m_GridTexture = pxl::Texture::Create(gridImage, textureSpecs);

        block = std::make_unique<TBlock>(glm::vec3(k_BlockBoardOrigin.x + k_UnitSize * 4.0f, k_BlockBoardOrigin.y + k_UnitSize * 6.0f, 0.2f));
    }

    Game::~Game()
    {
    }

    void Game::OnUpdate(float dt)
    {
        m_ElapsedTime += dt;

        if (m_ElapsedTime > m_FallTime)
        {
            // TEMP
            if (block->GetPosition().y - k_UnitSize < k_BoardBottomY)
            {
                m_ElapsedTime = 0.0f;
                return;
            }

            block->Translate({ 0.0f, -k_UnitSize, 0.0f });
            m_ElapsedTime = 0.0f;
        }
    }

    void Game::OnRender()
    {
        pxl::Quad board = {
            .Position = glm::vec3(0.0f),
            .Size = { 1024, 768 },
            .Origin = pxl::Origin2D::BottomLeft,
            .Texture = m_BoardTexture,
        };

        pxl::Quad grid = {
            .Position = glm::vec3(0.0f, 0.0f, 0.1f),
            .Size = { 1024, 768 },
            .Colour = { 1.0f, 1.0f, 1.0f, 0.2f },
            .Origin = pxl::Origin2D::BottomLeft,
            .Texture = m_GridTexture,
        };

        pxl::Renderer::AddQuad(board);
        pxl::Renderer::AddQuad(grid);

        // Draw blocks
        block->Draw();
    }

    void Game::OnGUIRender()
    {
    }

    void Game::OnClose()
    {
    }
}