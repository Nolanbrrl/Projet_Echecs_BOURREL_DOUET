#include "Board.hpp"
#include <imgui.h>
#include <iostream>
#include "quick_imgui/quick_imgui.hpp"

void Board::draw()
{
    float value{0.f};
    int   compteur_id = 0;
    quick_imgui::loop(
        "Chess",
        /* init: */ [&]() {},
        /* loop: */
        [&]() {
            ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!
            ImGui::Begin("Example");
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (i % 2 == 0 && j % 2 == 0)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 0.f}); // Changes the color of all buttons until we call ImGui::PopStyleColor(). There is also ImGuiCol_ButtonActive and ImGuiCol_ButtonHovered
                        ImGui::PushID(compteur_id);                                         // When some ImGui items have the same label (for exemple the next two buttons are labeled "Yo") ImGui needs you to specify an ID so that it can distinguish them. It can be an int, a pointer, a string, etc.
                                                                                            // You will definitely run into this when you create a button for each of your chess pieces, so remember to give them an ID!
                        if (ImGui::Button("B", ImVec2{50.f, 50.f}))
                            std::cout << "Clicked button 2\n";
                        ImGui::PopID(); // Then pop the id you pushed after you created the widget

                        ImGui::PopStyleColor();
                    }
                    else if (i % 2 == 0 && j % 2 == 1)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.f, 1.f, 1.f, 1.f});
                        ImGui::PushID(compteur_id);
                        if (ImGui::Button("A", ImVec2{50.f, 50.f}))
                            std::cout << "Clicked button 2\n";
                        ImGui::PopID();

                        ImGui::PopStyleColor();
                    }
                    else if (i % 2 == 1 && j % 2 == 0)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 0.f}); // Changes the color of all buttons until we call ImGui::PopStyleColor(). There is also ImGuiCol_ButtonActive and ImGuiCol_ButtonHovered
                        ImGui::PushID(compteur_id);                                         // When some ImGui items have the same label (for exemple the next two buttons are labeled "Yo") ImGui needs you to specify an ID so that it can distinguish them. It can be an int, a pointer, a string, etc.
                                                                                            // You will definitely run into this when you create a button for each of your chess pieces, so remember to give them an ID!
                        if (ImGui::Button("B", ImVec2{50.f, 50.f}))
                            std::cout << "Clicked button 2\n";
                        ImGui::PopID(); // Then pop the id you pushed after you created the widget

                        ImGui::PopStyleColor();
                    }
                    else if (i % 2 == 1 && j % 2 == 0)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.f, 1.f, 1.f, 1.f});
                        ImGui::PushID(compteur_id);
                        if (ImGui::Button("A", ImVec2{50.f, 50.f}))
                            std::cout << "Clicked button 2\n";
                        ImGui::PopID();

                        ImGui::PopStyleColor();
                    }
                    compteur_id++;
                    if (j < 7)
                    {
                        ImGui::SameLine();
                    }
                }
            }
            ImGui::End();
            // ImGui::SameLine(); // Draw the next ImGui widget on the same line as the previous one. Otherwise it would be below it

            // ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.f, 0.f, 0.f, 1.f}); // Changes the color of all buttons until we call ImGui::PopStyleColor(). There is also ImGuiCol_ButtonActive and ImGuiCol_ButtonHovered

            // ImGui::PushID(2); // When some ImGui items have the same label (for exemple the next two buttons are labeled "Yo") ImGui needs you to specify an ID so that it can distinguish them. It can be an int, a pointer, a string, etc.
            //                   // You will definitely run into this when you create a button for each of your chess pieces, so remember to give them an ID!
            // if (ImGui::Button("Yo", ImVec2{50.f, 50.f}))
            //     std::cout << "Clicked button 2\n";
            // ImGui::PopID(); // Then pop the id you pushed after you created the widget

            // ImGui::SameLine();
            // ImGui::PushID(3);
            // if (ImGui::Button("Yo", ImVec2{50.f, 50.f}))
            //     std::cout << "Clicked button 3\n";
            // ImGui::PopID();

            // ImGui::PopStyleColor();

            // ImGui::End();
        }
    );
}