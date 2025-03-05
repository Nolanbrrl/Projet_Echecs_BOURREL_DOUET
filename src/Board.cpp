#include "Board.hpp"
#include <imgui.h>
#include <algorithm>
#include <iostream>
#include <memory>
#include "Pieces/Cavalier.hpp"
#include "Pieces/Fou.hpp"
#include "Pieces/Piece.hpp"
#include "Pieces/Pion.hpp"
#include "Pieces/Reine.hpp"
#include "Pieces/Roi.hpp"
#include "Pieces/Tour.hpp"
#include "quick_imgui/quick_imgui.hpp"

Board::Board()
    : pieceMap{{
          {std::make_unique<Tour>(Color::noir, "T"), std::make_unique<Cavalier>(Color::noir, "C"), std::make_unique<Fou>(Color::noir, "F"), std::make_unique<Reine>(Color::noir, "Q"), std::make_unique<Roi>(Color::noir, "K"), std::make_unique<Fou>(Color::noir, "F"), std::make_unique<Cavalier>(Color::noir, "C"), std::make_unique<Tour>(Color::noir, "T")},
          {std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P"), std::make_unique<Pion>(Color::noir, "P")},
          {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
          {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
          {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
          {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
          {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
          {std::make_unique<Tour>(Color::blanc, "T"), std::make_unique<Cavalier>(Color::blanc, "C"), std::make_unique<Fou>(Color::blanc, "F"), std::make_unique<Roi>(Color::blanc, "K"), std::make_unique<Reine>(Color::blanc, "Q"), std::make_unique<Fou>(Color::blanc, "F"), std::make_unique<Cavalier>(Color::blanc, "C"), std::make_unique<Tour>(Color::blanc, "T")}
          // tableau de piece
      }}
{}

// std::optional<Piece *> Board::get_piece(Position pos) const
// {
//     if (pos.x < 0 || pos.x >= 8 || pos.y < 0 || pos.y >= 8)
//         return nullptr;

//     return pieceMap[pos.x][pos.y].get();
// }

void Board::draw()
{
    std::array<std::array<int, 8>, 8> tileMap{
        {{1, 0, 1, 0, 1, 0, 1, 0},
         {0, 1, 0, 1, 0, 1, 0, 1},
         {1, 0, 1, 0, 1, 0, 1, 0},
         {0, 1, 0, 1, 0, 1, 0, 1},
         {1, 0, 1, 0, 1, 0, 1, 0},
         {0, 1, 0, 1, 0, 1, 0, 1},
         {1, 0, 1, 0, 1, 0, 1, 0},
         {0, 1, 0, 1, 0, 1, 0, 1}
        }
    };

    quick_imgui::loop(
        "Chess",
        /* init: */ [&]() {},
        /* loop: */
        [&]() {
            ImGui::Begin("Plateau");
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0)); // Pas d'espacement entre les cases

            ImVec2 buttonSize = ImVec2{100.f, 100.f}; // Taille fixe des boutons

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    // Déterminer la couleur de base de la case
                    ImVec4 buttonColor = (tileMap[i][j] == 0) ? ImVec4{0.82f, 0.54f, 0.27f, 1.f} : ImVec4{1.f, 0.81f, 0.62f, 1.f};

                    // Vérifier si la case doit être surlignée
                    bool should_highlight = std::find(possible_moves.begin(), possible_moves.end(), Position{i, j}) != possible_moves.end();
                    if (should_highlight)
                        buttonColor = ImVec4{0.64f, 0.22f, 0.f, 1.f}; // Couleur des cases highlightées

                    // Appliquer la couleur
                    ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
                    ImGui::PushID(i * 8 + j); // ID unique pour éviter les conflits

                    bool clicked = false;

                    if (pieceMap[i][j] != nullptr)
                    {
                        clicked = ImGui::Button(pieceMap[i][j]->label().c_str(), buttonSize);
                    }
                    else
                    {
                        clicked = ImGui::Button("", buttonSize);
                    }

                    if (clicked)
                    {
                        if (pieceMap[i][j] != nullptr) // Sélectionner une pièce
                        {
                            selected_piece_position = {i, j};
                            possible_moves          = pieceMap[i][j]->list_all_possible_moves(*this, {i, j});
                        }
                        else if (should_highlight && selected_piece_position) // Déplacement de la pièce
                        {
                            auto [old_x, old_y] = selected_piece_position.value();

                            if (pieceMap[old_x][old_y] != nullptr)
                            {
                                pieceMap[i][j]         = std::move(pieceMap[old_x][old_y]);
                                pieceMap[old_x][old_y] = nullptr;

                                possible_moves.clear();
                                selected_piece_position.reset();
                            }
                        }
                    }

                    ImGui::PopID();
                    ImGui::PopStyleColor();

                    // S'assurer que les cases restent sur la même ligne
                    if (j < 7)
                        ImGui::SameLine();
                }
            }

            ImGui::PopStyleVar();
            ImGui::End();
        }
    );
}
