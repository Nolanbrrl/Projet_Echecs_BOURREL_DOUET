#include "Board.hpp"
#include <imgui.h>
#include <iostream>
#include "quick_imgui/quick_imgui.hpp"

Board::Board()
    : pieceMap{{
          {"T", "C", "F", "Q", "K", "F", "C", "T"},
          {"P", "P", "P", "P", "P", "P", "P", "P"},
          {"", "", "", "", "", "", "", ""},
          {"", "", "", "", "", "", "", ""},
          {"", "", "", "", "", "", "", ""},
          {"", "", "", "", "", "", "", ""},
          {"P", "P", "P", "P", "P", "P", "P", "P"},
          {"T", "C", "F", "K", "Q", "F", "C", "T"} //
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
            ImGui::Begin("Example");
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
                        ImGui::PushID(compteur_id);                                               // When some ImGui items have the same label (for exemple the next two buttons are labeled "Yo") ImGui needs you to specify an ID so that it can distinguish them. It can be an int, a pointer, a string, etc.                                                                  // You will definitely run into this when you create a button for each of your chess pieces, so remember to give them an ID!
                        ImGui::Button(pieceMap[i][j].c_str(), ImVec2{100.f, 100.f});
                        ImGui::PopID(); // Then pop the id you pushed after you created the widget
                        ImGui::PopStyleColor();
                    }
                    else if (tileMap[i][j] == 1)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.f, 0.81f, 0.62f, 1.f});
                        ImGui::PushID(compteur_id);
                        ImGui::Button(pieceMap[i][j].c_str(), ImVec2{100.f, 100.f});
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