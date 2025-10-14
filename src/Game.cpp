#include "Game.h"

#include "Blocks.h"

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
        pxl::Input::Init(window);

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

        pxl::GUI::Init(window);

        StartGame();
    }

    Game::~Game()
    {
    }

    void Game::OnUpdate(float dt)
    {
        m_ElapsedTime += dt;

        if (pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_A))
        {
            int validations = 0;
            for (const auto& segment : playerBlock->GetSegments())
            {
                if (CheckLeftSegment(segment.GetGridPosition()))
                {
                    validations++;
                }
            }

            if (validations == playerBlock->GetSegments().size())
                playerBlock->MoveLeft();
        }

        if (pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_D))
        {
            int validations = 0;
            for (const auto& segment : playerBlock->GetSegments())
            {
                if (CheckRightSegment(segment.GetGridPosition()))
                {
                    validations++;
                }
            }

            if (validations == playerBlock->GetSegments().size())
                playerBlock->MoveRight();
        }

        if (pxl::Input::IsKeyHeld(pxl::KeyCode::PXL_KEY_S))
        {
            // TODO: CONSTANT
            m_FallTime = 0.4f / 3;
        }
        else
        {
            m_FallTime = 0.4f;
        }

        if (m_ElapsedTime > m_FallTime)
        {
            for (const auto& segment : playerBlock->GetSegments())
            {
                if (!CheckBelowSegment(segment.GetGridPosition()))
                {
                    m_ElapsedTime = 0.0f;
                    PlacePlayerBlock();
                    if (!SpawnNewBlock(4, 18))
                    {
                        Close();
                        return;
                    }

                    return;
                }
            }

            playerBlock->MoveDown();
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

        pxl::Quad test;
        test.Position = { k_BlockBoardOrigin, 1.0f };

        pxl::Renderer::AddQuad(test);

        // Draw blocks
        playerBlock->Draw();

        for (int row = 0; row < sizeof(m_Grid) / sizeof(m_Grid[0]); row++)
        {
            for (int column = 0; column < sizeof(m_Grid[0]) / sizeof(m_Grid[0][0]); column++)
            {
                if (m_Grid[row][column].has_value())
                    pxl::Renderer::AddQuad(m_Grid[row][column].value().GetDrawQuad());
            }
        }
    }

    void Game::OnGUIRender()
    {
        ImGui::Begin("Falling Block Game Debug");

        ImGui::Text("%f, %f", playerBlock->GetPosition().x, playerBlock->GetPosition().y);
        ImGui::Text("%d, %d", playerBlock->GetGridPosition().x, playerBlock->GetGridPosition().y);

        ImGui::End();
    }

    void Game::OnClose()
    {
    }

    void Game::StartGame()
    {
        SpawnNewBlock(4, 18);
    }

    bool Game::SpawnNewBlock(int x, int y)
    {
        // Spawn a new block at the top of the board
        // Randomly pick from a new block to spawn
        // Check if the block will be able to spawn
        // If it can, spawn the block and return true
        // If it cannot, return false, which should finish the game

        // playerBlock = std::make_unique<TBlock>(glm::vec3(
        //     k_BlockBoardOrigin.x + k_UnitSize * 4.0f,
        //     k_BlockBoardOrigin.y + k_UnitSize * 6.0f,
        //     0.2f
        // ));

        auto randomBlock = pxl::Random::Float(0.0f, 1.0f);

        // if (randomBlock > 0.5f)
        // {
        //     playerBlock = std::make_unique<TBlock>(k_BlockBoardOrigin, glm::ivec2(x, y));
        // }
        // else
        // {
        //     playerBlock = std::make_unique<IBlock>(k_BlockBoardOrigin, glm::ivec2(x, y));
        // }

        playerBlock = std::make_unique<ZBlock>(k_BlockBoardOrigin, glm::ivec2(x, y));

        // switch (randomBlock)
        // {
        //     case 1: playerBlock = std::make_unique<TBlock>(k_BlockBoardOrigin, glm::ivec2(x, y)); break;
        //     case 2: playerBlock = std::make_unique<IBlock>(k_BlockBoardOrigin, glm::ivec2(x, y)); break;
        // }

        for (auto& segment : playerBlock->GetSegments())
        {
            auto gridPos = segment.GetGridPosition();
            if (m_Grid[gridPos.x][gridPos.y].has_value())
            {
                return false;
            }
        }

        return true;
    }

    bool Game::CheckBelowSegment(const glm::ivec2& gridPos)
    {
        if (gridPos.y <= 0)
            return false;

        if (m_Grid[gridPos.x][gridPos.y - 1].has_value())
        {
            return false;
        }

        return true;
    }

    bool Game::CheckLeftSegment(const glm::ivec2& gridPos)
    {
        if (gridPos.x <= 0)
            return false;

        if (m_Grid[gridPos.x - 1][gridPos.y].has_value())
        {
            return false;
        }

        return true;
    }

    bool Game::CheckRightSegment(const glm::ivec2& gridPos)
    {
        // TODO: Make 9 a constant
        if (gridPos.x >= 9)
            return false;

        if (m_Grid[gridPos.x + 1][gridPos.y].has_value())
        {
            return false;
        }

        return true;
    }

    void Game::PlacePlayerBlock()
    {
        for (const auto& segment : playerBlock->GetSegments())
        {
            auto segmentGridPos = segment.GetGridPosition();
            m_Grid[segmentGridPos.x][segmentGridPos.y] = segment;
        }

        // TODO: I need to reunderstand the rows and columns of the multidimensional array
        // Check each row for a full line

#if 0
        int rows = sizeof(m_Grid[0]) / sizeof(m_Grid[0][0]);
        int columns = sizeof(m_Grid) / sizeof(m_Grid[0]);

        for (int row = 0; row < rows; row++)
        {
            int columnsFilled = 0;
            for (int column = 0; column < columns; column++)
            {
                if (m_Grid[row][column].has_value())
                    columnsFilled++;
            }

            if (columnsFilled == 10)
            {
                // A line has been complete!
                // m_Grid[row].fill(std::array<std::optional<Segment>, 10>());
            }
        }

#endif
    }
}