#include "Game.h"

#include "Blocks/Blocks.h"

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

        // pxl::GUI::Init(window);

        StartNewGame();
    }

    Game::~Game()
    {
    }

    void Game::OnUpdate(float dt)
    {
        m_ElapsedTime += dt;

        // Move block left
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

        // Move block right
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

        // Faster soft drop
        m_FallTime = pxl::Input::IsKeyHeld(pxl::KeyCode::PXL_KEY_S) ? k_DefaultFallTime / 3 : k_DefaultFallTime;

        // Hard drop block
        if (pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_SPACE))
        {
            bool placedBlock = false;
            while (!placedBlock)
            {
                for (const auto& segment : playerBlock->GetSegments())
                {
                    if (!CheckBelowSegment(segment.GetGridPosition()))
                    {
                        PlacePlayerBlock();
                        // TODO: default spawn position constant
                        if (!SpawnNewBlock(4, 18))
                        {
                            StartNewGame();
                        }
                        placedBlock = true;

                        break;
                    }
                }

                if (!placedBlock)
                    playerBlock->MoveDown();
            }
        }

        // Hold block
        if (pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_LEFT_SHIFT))
        {
            SpawnNewBlock(4, 18);
        }

        // Reset game
        if (pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_R))
        {
            StartNewGame();
        }

        // Fall block over time
        if (m_ElapsedTime > m_FallTime)
        {
            for (const auto& segment : playerBlock->GetSegments())
            {
                if (!CheckBelowSegment(segment.GetGridPosition()))
                {
                    m_ElapsedTime = 0.0f;
                    PlacePlayerBlock();
                    // TODO: default spawn position constant
                    if (!SpawnNewBlock(4, 18))
                    {
                        StartNewGame();
                    }

                    break;
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

        // Draw blocks
        playerBlock->Draw();
        // hologramBlock->Draw();

        // Draw placed blocks
        for (int row = 0; row < sizeof(m_PlacedSegs) / sizeof(m_PlacedSegs[0]); row++)
        {
            for (int column = 0; column < sizeof(m_PlacedSegs[0]) / sizeof(m_PlacedSegs[0][0]); column++)
            {
                if (m_PlacedSegs[row][column].has_value())
                    pxl::Renderer::AddQuad(m_PlacedSegs[row][column].value().GetDrawQuad());
            }
        }
    }

    void Game::OnGUIRender()
    {
        // ImGui::Begin("Falling Block Game Debug");

        // ImGui::Text("%f, %f", playerBlock->GetPosition().x, playerBlock->GetPosition().y);
        // ImGui::Text("%d, %d", playerBlock->GetGridPosition().x, playerBlock->GetGridPosition().y);

        // ImGui::End();
    }

    void Game::OnClose()
    {
    }

    void Game::StartNewGame()
    {
        m_PlacedSegs.fill(std::array<std::optional<Segment>, 10>());
        SpawnNewBlock(4, 18);
    }

    bool Game::SpawnNewBlock(int x, int y)
    {
        // TODO: Spawn a new block at the top of the board
        // Randomly pick from a new block to spawn
        // Check if the block will be able to spawn
        // If it can, spawn the block and return true
        // If it cannot, return false, which should finish the game

        m_ElapsedTime = 0.0f;

        auto randomBlock = pxl::Random::UInt(1, 7);

        switch (randomBlock)
        {
            case 1: playerBlock = std::make_unique<TBlock>(k_BlockBoardOrigin, glm::ivec2(x, y)); break;
            case 2: playerBlock = std::make_unique<IBlock>(k_BlockBoardOrigin, glm::ivec2(x, y)); break;
            case 3: playerBlock = std::make_unique<ZBlock>(k_BlockBoardOrigin, glm::ivec2(x, y)); break;
            case 4: playerBlock = std::make_unique<SBlock>(k_BlockBoardOrigin, glm::ivec2(x, y)); break;
            case 5: playerBlock = std::make_unique<OBlock>(k_BlockBoardOrigin, glm::ivec2(x, y)); break;
            case 6: playerBlock = std::make_unique<LBlock>(k_BlockBoardOrigin, glm::ivec2(x, y)); break;
            case 7: playerBlock = std::make_unique<JBlock>(k_BlockBoardOrigin, glm::ivec2(x, y)); break;
        }

        for (auto& segment : playerBlock->GetSegments())
        {
            auto gridPos = segment.GetGridPosition();

            if (m_PlacedSegs[gridPos.y][gridPos.x].has_value())
                return false;
        }

        return true;
    }

    bool Game::CheckBelowSegment(const glm::ivec2& gridPos)
    {
        if (gridPos.y <= 0)
            return false;

        if (m_PlacedSegs[gridPos.y - 1][gridPos.x].has_value())
            return false;
        

        return true;
    }

    bool Game::CheckLeftSegment(const glm::ivec2& gridPos)
    {
        if (gridPos.x <= 0)
            return false;

        if (m_PlacedSegs[gridPos.y][gridPos.x - 1].has_value())
            return false;

        return true;
    }

    bool Game::CheckRightSegment(const glm::ivec2& gridPos)
    {
        // TODO: Make 9 a constant
        if (gridPos.x >= 9)
            return false;

        if (m_PlacedSegs[gridPos.y][gridPos.x + 1].has_value())
            return false;

        return true;
    }

    void Game::PlacePlayerBlock()
    {
        // Place block
        for (const auto& segment : playerBlock->GetSegments())
        {
            auto segmentGridPos = segment.GetGridPosition();
            m_PlacedSegs[segmentGridPos.y][segmentGridPos.x] = segment;
        }

        auto rows = sizeof(m_PlacedSegs) / sizeof(m_PlacedSegs[0]);
        auto columns = sizeof(m_PlacedSegs[0]) / sizeof(m_PlacedSegs[0][0]);

        // Check for completed lines
        // TODO: size_t instead of int32_t on rows breaks the for loop (need to investigate)
        for (int32_t row = rows - 1; row >= 0; row--)
        {
            uint32_t segsInRow = 0;
            for (size_t column = 0; column < columns; column++)
            {
                if (m_PlacedSegs[row][column].has_value())
                    segsInRow++;
            }

            if (segsInRow >= 10)
            {
                // Clear the line
                m_PlacedSegs[row].fill(std::optional<Segment>());

                // Move above lines down
                for (size_t aboveRow = row; aboveRow < rows; aboveRow++)
                {
                    if (aboveRow == 19)
                        break;

                    m_PlacedSegs[aboveRow] = m_PlacedSegs[aboveRow + 1];

                    for (auto& segment : m_PlacedSegs[aboveRow])
                    {
                        if (segment.has_value())
                            segment->Translate({ 0, -1 });
                    }
                }
            }
        }
    }
}