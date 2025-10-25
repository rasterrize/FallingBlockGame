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

#if PXL_DEBUG
        pxl::GUI::Init(window);
#endif

        StartNewGame();
    }

    Game::~Game()
    {
    }

    void Game::OnUpdate(float dt)
    {
        m_ElapsedTime += dt;

        // Move block left
        if (pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_A) || pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_LEFT))
        {
            int validations = 0;
            for (const auto& segment : m_PlayerBlock->GetSegments())
            {
                if (IsEmptyLeft(segment.GetGridPosition()))
                {
                    validations++;
                }
            }

            if (validations == m_PlayerBlock->GetSegments().size())
                m_PlayerBlock->MoveLeft();
        }

        // Move block right
        if (pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_D) || pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_RIGHT))
        {
            int validations = 0;
            for (const auto& segment : m_PlayerBlock->GetSegments())
            {
                if (IsEmptyRight(segment.GetGridPosition()))
                {
                    validations++;
                }
            }

            if (validations == m_PlayerBlock->GetSegments().size())
                m_PlayerBlock->MoveRight();
        }

        // Faster soft drop
        if (pxl::Input::IsKeyHeld(pxl::KeyCode::PXL_KEY_S) || pxl::Input::IsKeyHeld(pxl::KeyCode::PXL_KEY_DOWN))
        {
            if (m_CurrentFallTime == m_FallTimeSetting)
                m_CurrentFallTime /= m_SoftDropSpeed;
        }
        else
        {
            m_CurrentFallTime = m_FallTimeSetting;
        }

        // Hard drop block
        if (pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_SPACE))
        {
            bool placedBlock = false;
            while (!placedBlock)
            {
                for (const auto& segment : m_PlayerBlock->GetSegments())
                {
                    if (!IsEmptyBelow(segment.GetGridPosition()))
                    {
                        if (CanPlacePlayerBlock())
                        {
                            PlacePlayerBlock();
                            NextPlayerBlock();
                            GenerateRandomBlock(4, 19);
                        }
                        else
                        {
                            StartNewGame();
                        }

                        placedBlock = true;

                        break;
                    }
                }

                if (!placedBlock)
                    m_PlayerBlock->MoveDown();
            }
        }

        // Hold block
        if (pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_LEFT_SHIFT))
        {
            m_HeldBlock.swap(m_PlayerBlock);

            if (!m_PlayerBlock)
                NextPlayerBlock();

            m_PlayerBlock->SetGridPosition({ 4, 18 });
        }

        // Rotate left
        if (pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_Q) || pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_Z))
        {
            m_PlayerBlock->RotateLeft();

            CheckBoundsAndMove();

            // Check if rotation is valid, if not, undo
            for (auto& segment : m_PlayerBlock->GetSegments())
            {
                auto gridPos = segment.GetGridPosition();
                if (m_PlacedSegs[gridPos.y][gridPos.x].has_value())
                {
                    m_PlayerBlock->RotateRight();
                    break;
                }
            }
        }

        // Rotate right
        if (pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_E) || pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_X))
        {
            m_PlayerBlock->RotateRight();

            CheckBoundsAndMove();

            // Check if rotation is valid, if not, undo
            for (auto& segment : m_PlayerBlock->GetSegments())
            {
                auto gridPos = segment.GetGridPosition();
                if (m_PlacedSegs[gridPos.y][gridPos.x].has_value())
                {
                    m_PlayerBlock->RotateLeft();
                    break;
                }
            }
        }

        // Rotate 180
        if (pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_F) || pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_C))
        {
            m_PlayerBlock->Rotate180();

            CheckBoundsAndMove();

            // Check if rotation is valid, if not, undo
            for (auto& segment : m_PlayerBlock->GetSegments())
            {
                auto gridPos = segment.GetGridPosition();
                if (m_PlacedSegs[gridPos.y][gridPos.x].has_value())
                {
                    m_PlayerBlock->Rotate180();
                    break;
                }
            }
        }

        // Reset game
        if (pxl::Input::IsKeyPressed(pxl::KeyCode::PXL_KEY_R))
        {
            StartNewGame();
        }

        // Fall block over time
        if (m_ElapsedTime > m_CurrentFallTime)
        {
            for (const auto& segment : m_PlayerBlock->GetSegments())
            {
                if (!IsEmptyBelow(segment.GetGridPosition()))
                {
                    if (CanPlacePlayerBlock())
                    {
                        PlacePlayerBlock();
                        NextPlayerBlock();
                    }
                    else
                    {
                        StartNewGame();
                    }

                    break;
                }
            }

            m_PlayerBlock->MoveDown();
            m_ElapsedTime = 0.0f;
        }

        // Update hologram
        for (int i = 0; i < m_PlayerBlock->GetSegments().size(); i++)
        {
            m_HologramSegments[i] = m_PlayerBlock->GetSegments()[i];
            m_HologramSegments[i].SetColour({ 1.0f, 1.0f, 1.0f, 0.25f });
        }

        bool foundPlacement = false;
        while (!foundPlacement)
        {
            for (const auto& segment : m_HologramSegments)
            {
                if (!IsEmptyBelow(segment.GetGridPosition()))
                {
                    foundPlacement = true;
                    break;
                }
            }

            if (!foundPlacement)
            {
                for (auto& segment : m_HologramSegments)
                {
                    segment.Translate({ 0, -1 });
                }
            }
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
        m_PlayerBlock->Draw();

        // Draw hologram
        for (auto& segment : m_HologramSegments)
        {
            auto quad = segment.GetDrawQuad();
            quad.Size += glm::vec2(1.0f, 1.0f);
            pxl::Renderer::AddQuad(quad);
        }

        // Draw placed blocks
        for (int row = 0; row < sizeof(m_PlacedSegs) / sizeof(m_PlacedSegs[0]); row++)
        {
            for (int column = 0; column < sizeof(m_PlacedSegs[0]) / sizeof(m_PlacedSegs[0][0]); column++)
            {
                if (m_PlacedSegs[row][column].has_value())
                    pxl::Renderer::AddQuad(m_PlacedSegs[row][column].value().GetDrawQuad());
            }
        }

        // Draw block bag
        for (int i = 0; i < m_BlockBag.size(); i++)
        {
            auto segments = m_BlockBag[i]->GetSegments();

            for (auto& segment : segments)
            {
                auto quad = segment.GetDrawQuad();
                quad.Position += glm::vec3(400.0f, -30.0f - (i * 150.0f), 0.4f);

                pxl::Renderer::AddQuad(quad);
            }
        }

        // Draw held block
        if (m_HeldBlock)
        {
            auto segments = m_HeldBlock->GetSegments();

            for (auto& segment : segments)
            {
                auto quad = segment.GetDrawQuad();
                quad.Position += glm::vec3(-400.0f, 0, 0.4f);

                pxl::Renderer::AddQuad(quad);
            }
        }
    }

    void Game::OnGUIRender()
    {
        ImGui::Begin("Falling Block Game Debug");

        // ImGui::Text("Block Pos Actual: %f, %f", m_PlayerBlock->GetPosition().x, m_PlayerBlock->GetPosition().y);
        ImGui::Text("Block Grid Pos: %d, %d", m_PlayerBlock->GetGridPosition().x, m_PlayerBlock->GetGridPosition().y);
        ImGui::Text("Block Rotation Index: %d", m_PlayerBlock->GetRotationIndex());
        ImGui::InputFloat("Fall Time:", &m_FallTimeSetting);

        ImGui::End();
    }

    void Game::OnClose()
    {
    }

    void Game::StartNewGame()
    {
        m_PlacedSegs.fill(std::array<std::optional<Segment>, 10>());

        m_BlockBag.clear();

        m_PlayerBlock = GenerateRandomBlock(4, 18);

        for (int i = 0; i < 5; i++)
            m_BlockBag.push_back(GenerateRandomBlock(4, 18));
    }

    std::unique_ptr<Block> Game::GenerateRandomBlock(int x, int y)
    {
        auto randomBlock = pxl::Random::UInt(1, 7);

        switch (randomBlock)
        {
            case 1: return std::make_unique<TBlock>(k_BlockBoardOrigin, glm::ivec2(x, y));
            case 2: return std::make_unique<IBlock>(k_BlockBoardOrigin, glm::ivec2(x, y));
            case 3: return std::make_unique<SBlock>(k_BlockBoardOrigin, glm::ivec2(x, y));
            case 4: return std::make_unique<ZBlock>(k_BlockBoardOrigin, glm::ivec2(x, y));
            case 5: return std::make_unique<OBlock>(k_BlockBoardOrigin, glm::ivec2(x, y));
            case 6: return std::make_unique<LBlock>(k_BlockBoardOrigin, glm::ivec2(x, y));
            case 7: return std::make_unique<JBlock>(k_BlockBoardOrigin, glm::ivec2(x, y));
        }

        return nullptr;
    }

    bool Game::IsEmptyBelow(const glm::ivec2& gridPos)
    {
        if (gridPos.y <= 0)
            return false;

        if (m_PlacedSegs[gridPos.y - 1][gridPos.x].has_value())
            return false;

        return true;
    }

    bool Game::IsEmptyLeft(const glm::ivec2& gridPos)
    {
        if (gridPos.x <= 0)
            return false;

        if (m_PlacedSegs[gridPos.y][gridPos.x - 1].has_value())
            return false;

        return true;
    }

    bool Game::IsEmptyRight(const glm::ivec2& gridPos)
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
        for (const auto& segment : m_PlayerBlock->GetSegments())
        {
            auto segmentGridPos = segment.GetGridPosition();
            m_PlacedSegs[segmentGridPos.y][segmentGridPos.x] = segment;
        }

        auto rows = sizeof(m_PlacedSegs) / sizeof(m_PlacedSegs[0]);
        auto columns = sizeof(m_PlacedSegs[0]) / sizeof(m_PlacedSegs[0][0]);

        // Check for completed lines
        // TODO: size_t instead of int32_t on rows breaks the for loop (need to investigate)
        for (int32_t row = static_cast<int32_t>(rows) - 1; row >= 0; row--)
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

    void Game::CheckBoundsAndMove()
    {
        // Validate segments
        for (int i = 0; i < m_PlayerBlock->GetSegments().size(); i++)
        {
            uint32_t checksPassed = 0;
            while (checksPassed < 4)
            {
                // Check if segment is in grid bounds
                auto gridPos = m_PlayerBlock->GetSegments()[i].GetGridPosition();
                if (gridPos.x < 0)
                {
                    // Segment is outside on the left so move block right
                    m_PlayerBlock->MoveRight();
                }
                else
                {
                    checksPassed++;
                }

                if (gridPos.x >= static_cast<int32_t>(m_PlacedSegs[0].size()))
                {
                    // Segment is outside on the right so move block left
                    m_PlayerBlock->MoveLeft();
                }
                else
                {
                    checksPassed++;
                }

                if (gridPos.y >= static_cast<int32_t>(m_PlacedSegs.size()))
                {
                    m_PlayerBlock->MoveDown();
                }
                else
                {
                    checksPassed++;
                }

                if (gridPos.y < 0)
                {
                    m_PlayerBlock->Translate({ 0, 1 });
                }
                else
                {
                    checksPassed++;
                }
            }
        }
    }

    void Game::NextPlayerBlock()
    {
        m_ElapsedTime = 0.0f;

        m_PlayerBlock.swap(m_BlockBag.front());

        m_BlockBag.erase(m_BlockBag.begin());

        m_BlockBag.push_back(GenerateRandomBlock(4, 18));
    }

    bool Game::CanPlacePlayerBlock()
    {
        for (auto& segment : m_PlayerBlock->GetSegments())
        {
            auto gridPos = segment.GetGridPosition();

            if (m_PlacedSegs[gridPos.y][gridPos.x].has_value())
                return false;
        }

        return true;
    }

    void Game::SetupHologram()
    {
        for (int i = 0; i < m_PlayerBlock->GetSegments().size(); i++)
        {
            m_HologramSegments[i] = m_PlayerBlock->GetSegments()[i];
            m_HologramSegments[i].SetColour({ 1.0f, 1.0f, 1.0f, 0.25f });
        }
    }
}