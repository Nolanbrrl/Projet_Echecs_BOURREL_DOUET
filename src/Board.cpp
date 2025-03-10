#include "Board.hpp"
#include <imgui.h>
#include <algorithm>
#include <cstddef>
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
          {std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P"), std::make_unique<Pion>(Color::blanc, "P")},
          {std::make_unique<Tour>(Color::blanc, "T"), std::make_unique<Cavalier>(Color::blanc, "C"), std::make_unique<Fou>(Color::blanc, "F"), std::make_unique<Roi>(Color::blanc, "K"), std::make_unique<Reine>(Color::blanc, "Q"), std::make_unique<Fou>(Color::blanc, "F"), std::make_unique<Cavalier>(Color::blanc, "C"), std::make_unique<Tour>(Color::blanc, "T")}
          // tableau de piece
      }}
{}

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
        {std::make_unique<Tour>(Color::blanc, "T"), std::make_unique<Cavalier>(Color::blanc, "C"), std::make_unique<Fou>(Color::blanc, "F"), std::make_unique<Roi>(Color::blanc, "K"), std::make_unique<Reine>(Color::blanc, "Q"), std::make_unique<Fou>(Color::blanc, "F"), std::make_unique<Cavalier>(Color::blanc, "C"), std::make_unique<Tour>(Color::blanc, "T")}
        // tableau de piece
    }};
    cimetiere_piece_noire.clear();
    cimetiere_piece_blanche.clear();
    selected_piece_position.reset();
    possible_moves.clear();
    pion_pour_prise_en_passant.reset();
    partie_terminee = false;
}

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
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

            ImVec2 buttonSize = ImVec2{100.f, 100.f};

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    ImVec4 buttonColor = (tileMap[i][j] == 0) ? ImVec4{0.82f, 0.54f, 0.27f, 1.f} : ImVec4{1.f, 0.81f, 0.62f, 1.f};

                    bool should_highlight = std::find(possible_moves.begin(), possible_moves.end(), Position{i, j}) != possible_moves.end();
                    if (should_highlight)
                        buttonColor = ImVec4{0.64f, 0.22f, 0.f, 1.f};

                    ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
                    ImGui::PushID(i * 8 + j);

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
                        if (should_highlight && selected_piece_position)
                        {
                            auto [old_x, old_y] = selected_piece_position.value();

                            if (pieceMap[old_x][old_y] != nullptr)
                            {
                                if (pieceMap[i][j] != nullptr && pieceMap[i][j]->label() == "K")
                                {
                                    partie_terminee = true;
                                }
                                if (pieceMap[old_x][old_y]->label() == "P")
                                {
                                    if (std::abs(old_x - i) == 2)
                                    {
                                        pion_pour_prise_en_passant = Position{i, j};
                                    }
                                    else
                                    {
                                        pion_pour_prise_en_passant.reset();
                                    }
                                }
                                if (pieceMap[i][j] != nullptr && pieceMap[i][j]->getColor() == Color::noir)
                                {
                                    cimetiere_piece_noire.push_back(std::move(pieceMap[i][j]));
                                    std::cout << "cim noir : " << cimetiere_piece_noire[0] << '\n';
                                }
                                else if (pieceMap[i][j] != nullptr && pieceMap[i][j]->getColor() == Color::blanc)
                                {
                                    cimetiere_piece_blanche.push_back(std::move(pieceMap[i][j]));
                                    std::cout << "cim blanc : " << cimetiere_piece_blanche[0] << '\n';
                                }

                                if (pion_pour_prise_en_passant.has_value())
                                {
                                    Position passant_pion = pion_pour_prise_en_passant.value();

                                    if (pieceMap[old_x][old_y]->label() == "P" && old_x == passant_pion.x && std::abs(old_y - passant_pion.y) == 1 && i == passant_pion.x + (pieceMap[old_x][old_y]->getColor() == Color::blanc ? -1 : 1))
                                    {
                                        if (pieceMap[passant_pion.x][passant_pion.y] != nullptr)
                                        {
                                            if (pieceMap[passant_pion.x][passant_pion.y]->getColor() == Color::noir)
                                            {
                                                cimetiere_piece_noire.push_back(std::move(pieceMap[passant_pion.x][passant_pion.y]));
                                            }
                                            else if (pieceMap[passant_pion.x][passant_pion.y]->getColor() == Color::blanc)
                                            {
                                                cimetiere_piece_blanche.push_back(std::move(pieceMap[passant_pion.x][passant_pion.y]));
                                            }
                                        }
                                        pieceMap[passant_pion.x][passant_pion.y] = nullptr;
                                        pion_pour_prise_en_passant.reset();
                                    }
                                }

                                pieceMap[i][j]         = std::move(pieceMap[old_x][old_y]);
                                pieceMap[old_x][old_y] = nullptr;

                                tour_actuel = (tour_actuel == Color::blanc) ? Color::noir : Color::blanc;

                                possible_moves.clear();
                                selected_piece_position.reset();
                            }
                        }
                        else if (pieceMap[i][j] != nullptr)
                        {
                            if (tour_actuel == pieceMap[i][j]->getColor())
                            {
                                selected_piece_position = {i, j};
                                possible_moves          = pieceMap[i][j]->list_all_possible_moves(*this, {i, j});
                            }
                        }
                    }

                    ImGui::PopID();
                    ImGui::PopStyleColor();

                    if (j < 7)
                        ImGui::SameLine();
                }
            }

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

            ImGui::PopStyleVar();
            ImGui::End();
        }
    );
}
