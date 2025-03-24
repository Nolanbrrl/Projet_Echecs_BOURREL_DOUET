#include "Board.hpp"
#include <glad/glad.h>
#include <imgui.h>
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include "Pieces/Cavalier.hpp"
#include "Pieces/Fou.hpp"
#include "Pieces/Piece.hpp"
#include "Pieces/Pion.hpp"
#include "Pieces/Reine.hpp"
#include "Pieces/Roi.hpp"
#include "Pieces/Tour.hpp"
#include "glimac/FilePath.hpp"
#include "glimac/Program.hpp"
#include "glimac/Sphere.hpp"
#include "quick_imgui/quick_imgui.hpp"

Board::Board()
    : pieceMap{{
          {std::make_unique<Tour>(Color::noir, "T"), std::make_unique<Cavalier>(Color::noir, "C"), std::make_unique<Fou>(Color::noir, "F"), std::make_unique<Reine>(Color::noir, "Q"), std::make_unique<Roi>(Color::noir, "K"), std::make_unique<Fou>(Color::noir, "F"), std::make_unique<Cavalier>(Color::noir, "C"), std::make_unique<Tour>(Color::noir, "T")},
          {std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P")},
          {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
          {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
          {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
          {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
          {std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P")},
          {std::make_unique<Tour>(Color::blanc, "T"), std::make_unique<Cavalier>(Color::blanc, "C"), std::make_unique<Fou>(Color::blanc, "F"), std::make_unique<Reine>(Color::blanc, "Q"), std::make_unique<Roi>(Color::blanc, "K"), std::make_unique<Fou>(Color::blanc, "F"), std::make_unique<Cavalier>(Color::blanc, "C"), std::make_unique<Tour>(Color::blanc, "T")}
          // commentaire pour l'alignement de ces fucking lignes
      }}
{
    initializeBoard();
}

void Board::resetBoard()
{
    pieceMap = {{
        {std::make_unique<Tour>(Color::noir, "T"), std::make_unique<Cavalier>(Color::noir, "C"), std::make_unique<Fou>(Color::noir, "F"), std::make_unique<Reine>(Color::noir, "Q"), std::make_unique<Roi>(Color::noir, "K"), std::make_unique<Fou>(Color::noir, "F"), std::make_unique<Cavalier>(Color::noir, "C"), std::make_unique<Tour>(Color::noir, "T")},
        {std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P")},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P")},
        {std::make_unique<Tour>(Color::blanc, "T"), std::make_unique<Cavalier>(Color::blanc, "C"), std::make_unique<Fou>(Color::blanc, "F"), std::make_unique<Reine>(Color::blanc, "Q"), std::make_unique<Roi>(Color::blanc, "K"), std::make_unique<Fou>(Color::blanc, "F"), std::make_unique<Cavalier>(Color::blanc, "C"), std::make_unique<Tour>(Color::blanc, "T")}
        // commentaire pour l'alignement de ces fucking lignes encore
    }};
    cimetiere_piece_noire.clear();
    cimetiere_piece_blanche.clear();
    selected_piece_position.reset();
    possible_moves.clear();
    pion_pour_prise_en_passant.reset();
    partie_terminee = false;
}

void Board::initializeBoard()
{
    tileMap = {
        {{1, 0, 1, 0, 1, 0, 1, 0},
         {0, 1, 0, 1, 0, 1, 0, 1},
         {1, 0, 1, 0, 1, 0, 1, 0},
         {0, 1, 0, 1, 0, 1, 0, 1},
         {1, 0, 1, 0, 1, 0, 1, 0},
         {0, 1, 0, 1, 0, 1, 0, 1},
         {1, 0, 1, 0, 1, 0, 1, 0},
         {0, 1, 0, 1, 0, 1, 0, 1}}
        // commentaire pour l'alignement de ces fucking lignes ENCORE
    };
}

void Board::drawBoard()
{
    ImVec2 buttonSize = ImVec2{100.f, 100.f};

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
    {
        selected_piece_position.reset();
        possible_moves.clear();
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            ImVec4 buttonColor      = (tileMap[i][j] == 0) ? ImVec4{0.82f, 0.54f, 0.27f, 1.f} : ImVec4{1.f, 0.81f, 0.62f, 1.f};
            bool   should_highlight = std::find(possible_moves.begin(), possible_moves.end(), Position{i, j}) != possible_moves.end();
            if (should_highlight)
                buttonColor = ImVec4{0.64f, 0.22f, 0.f, 1.f};

            ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
            ImGui::PushID(i * 8 + j);

            bool clicked = false;
            if (pieceMap[i][j] != nullptr)
            {
                ImVec4 pieceColor = (pieceMap[i][j]->getColor() == Color::noir) ? ImVec4{0.f, 0.f, 0.f, 1.f} : ImVec4{1.f, 1.f, 1.f, 1.f};
                ImGui::PushStyleColor(ImGuiCol_Text, pieceColor);
                clicked = ImGui::Button(pieceMap[i][j]->label().c_str(), buttonSize);
                ImGui::PopStyleColor();
            }
            else
            {
                clicked = ImGui::Button("", buttonSize);
            }

            if (clicked)
                handleClick(i, j);

            ImGui::PopID();
            ImGui::PopStyleColor();

            if (j < 7)
                ImGui::SameLine();
        }
    }
}

void Board::handleClick(int i, int j)
{
    if (selected_piece_position && std::find(possible_moves.begin(), possible_moves.end(), Position{i, j}) != possible_moves.end())
    {
        auto [old_x, old_y] = selected_piece_position.value();
        if (pieceMap[old_x][old_y] != nullptr)
        {
            if (pieceMap[i][j] != nullptr && pieceMap[i][j]->label() == "K")
                partie_terminee = true;

            if (pieceMap[old_x][old_y]->label() == "P" && std::abs(old_x - i) == 2)
                pion_pour_prise_en_passant = Position{i, j};

            else
            {
                if (pieceMap[old_x][old_y]->label() == "P" && pion_pour_prise_en_passant.has_value() && ((pion_pour_prise_en_passant.value().x + 1 == i && pieceMap[old_x][old_y]->getColor() == Color::noir) || (pion_pour_prise_en_passant.value().x - 1 == i && pieceMap[old_x][old_y]->getColor() == Color::blanc)) && pion_pour_prise_en_passant.value().y == j)
                {
                    pieceMap[pion_pour_prise_en_passant.value().x][pion_pour_prise_en_passant.value().y] = nullptr;
                }

                pion_pour_prise_en_passant.reset();
            }

            if (pieceMap[i][j] != nullptr)
            {
                if (pieceMap[i][j]->getColor() == Color::noir)
                    cimetiere_piece_noire.push_back(std::move(pieceMap[i][j]));
                else
                    cimetiere_piece_blanche.push_back(std::move(pieceMap[i][j]));
            }
            pieceMap[i][j]         = std::move(pieceMap[old_x][old_y]);
            pieceMap[old_x][old_y] = nullptr;
            tour_actuel            = (tour_actuel == Color::blanc) ? Color::noir : Color::blanc;
        }

        possible_moves.clear();
        selected_piece_position.reset();
    }
    else if (pieceMap[i][j] != nullptr && tour_actuel == pieceMap[i][j]->getColor())
    {
        selected_piece_position = {i, j};
        possible_moves          = pieceMap[i][j]->list_all_possible_moves(*this, {i, j});
    }
}

void Board::checkGameOver()
{
    if (partie_terminee)
    {
        ImGui::OpenPopup("Partie terminée");
    }

    if (ImGui::BeginPopupModal("Partie terminée", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Le roi a été mangé. La partie est terminée !");
        if (ImGui::Button("OK"))
        {
            resetBoard();
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

GLuint vaos[16];

GLuint vbos[16];

void drawCube(const ImVec4& color)
{
    static const GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, // Back face
        -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f,     // Front face
        -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f,     // Top face
        -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, // Bottom face
        0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f,     // Right face
        -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f  // Left face
    };

    static const GLuint indices[] = {
        0, 1, 2, 2, 3, 0,       // Back face
        4, 5, 6, 6, 7, 4,       // Front face
        8, 9, 10, 10, 11, 8,    // Top face
        12, 13, 14, 14, 15, 12, // Bottom face
        16, 17, 18, 18, 19, 16, // Right face
        20, 21, 22, 22, 23, 20  // Left face
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glColor4f(color.x, color.y, color.z, color.w);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void Board::draw(int argc, char** argv)
{
    quick_imgui::loop(
        "Quick ImGui",
        {
            .init = [argv]() {
                std::cout << "Init\n";
                glimac::FilePath applicationPath(argv[0]);
                glimac::Program program =
                    loadProgram(applicationPath.dirPath() + "/src/Shaders/vertex_shader.glsl",
                                applicationPath.dirPath() + "/src/Shaders/fragment_shader.glsl");
                program.use();

                glEnable(GL_DEPTH_TEST); // Activer le test de profondeur

                glGenBuffers(16, vbos);
                glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);

                glBindBuffer(GL_ARRAY_BUFFER, 0);

                glGenVertexArrays(16, vaos);
                glBindVertexArray(vaos[0]);
                const GLuint VERTEX_ATTR_POSITION = 0;
                const GLuint VERTEX_ATTR_COLOR = 1;
                glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);

                glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
                glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE,
                                      sizeof(glimac::ShapeVertex), 0);

                glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
                glVertexAttribPointer(VERTEX_ATTR_COLOR, 2, GL_FLOAT, GL_FALSE,
                                      sizeof(glimac::ShapeVertex),
                                      (const GLvoid *)(offsetof(glimac::ShapeVertex, texCoords)));

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0); },
            .loop = [this]() {
                ImGui::ShowDemoWindow();

                ImGui::Begin("Plateau");
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

                drawBoard();
                checkGameOver();

                glClearColor(0.9f, 0.9f, 0.9f, 1.00f); // Fond gris clair
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Nettoyer le Z-buffer
                glBindVertexArray(vaos[0]);

                for (int i = 0; i < 8; ++i) {
                    for (int j = 0; j < 8; ++j) {
                        glPushMatrix();
                        glTranslatef(i - 3.5f, j - 3.5f, 0.0f);

                        ImVec4 color = (tileMap[i][j] == 0) ? ImVec4{0.82f, 0.54f, 0.27f, 1.f} : ImVec4{1.f, 0.81f, 0.62f, 1.f};
                        drawCube(color);

                        glPopMatrix();
                    }
                }

                glBindVertexArray(0);

                ImGui::PopStyleVar();
                ImGui::End(); },
        }
    );
    glDeleteBuffers(16, vbos);
    glDeleteVertexArrays(16, vaos);
}