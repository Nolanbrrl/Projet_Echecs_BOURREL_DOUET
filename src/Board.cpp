#include "Board.hpp"
#include <imgui.h>
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

void Board::draw()
{
    std::array<std::array<int, 8>, 8> tileMap{
        {
            {1, 0, 1, 0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0, 1, 0, 1} //
        }
    };

    float value{0.f};
    int   compteur_id = 0;
    quick_imgui::loop(
        "Chess",
        /* init: */ [&]() {},
        /* loop: */
        [&]() {
            ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!
            ImGui::Begin("Plateau");
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (j != 0)
                    {
                        ImGui::SameLine();
                    }
                    if (tileMap[i][j] == 0)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.82f, 0.54f, 0.27f, 1.f}); // Changes the color of all buttons until we call ImGui::PopStyleColor(). There is also ImGuiCol_ButtonActive and ImGuiCol_ButtonHovered
                        ImGui::PushID(compteur_id);

                        // JUSTE AVANT DE FAIRE AFFICHER AVEC LE LABEL IL FAUT FAIRE UNE VERIF EN MODE EXISTE T IL UNE PIECE SUR CETTE CASE ? en gros si c pas null pointer alors on fait la ligne suivante sinon nan
                        if (pieceMap[i][j] != nullptr)
                        {
                            ImGui::Button(pieceMap[i][j]->label().c_str(), ImVec2{100.f, 100.f});
                        }
                        else
                        {
                            ImGui::Button("", ImVec2{100.f, 100.f});
                        }
                        ImGui::PopID(); // Then pop the id you pushed after you created the widget
                        ImGui::PopStyleColor();
                    }
                    else if (tileMap[i][j] == 1)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.f, 0.81f, 0.62f, 1.f});
                        ImGui::PushID(compteur_id);
                        if (pieceMap[i][j] != nullptr)
                        {
                            ImGui::Button(pieceMap[i][j]->label().c_str(), ImVec2{100.f, 100.f});
                        }
                        else
                        {
                            ImGui::Button("", ImVec2{100.f, 100.f});
                        }
                        ImGui::PopID();

                        ImGui::PopStyleColor();
                    }

                    compteur_id++;
                }
            }
            ImGui::PopStyleVar(1);
            ImGui::End();
        }
    );
}