#include "Board.hpp"
#include <glad/glad.h>
#include <imgui.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "Pieces/Cavalier.hpp"
#include "Pieces/Fou.hpp"
#include "Pieces/Piece.hpp"
#include "Pieces/Pion.hpp"
#include "Pieces/Reine.hpp"
#include "Pieces/Roi.hpp"
#include "Pieces/Tour.hpp"

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
    promo_en_cours  = false;
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

void Board::gerer_promotion()
{
    if (!promo_en_cours)
        return;

    ImGui::OpenPopup("Promouvoir le pion");

    if (ImGui::BeginPopupModal("Promouvoir le pion", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Choisissez votre nouvelle pièce :");

        Color  couleur_pion  = pieceMap[pos_pion_a_promouvoir.x][pos_pion_a_promouvoir.y]->getColor();
        ImVec4 couleur_texte = (couleur_pion == Color::noir) ? ImVec4{0.f, 0.f, 0.f, 1.f} : ImVec4{1.f, 1.f, 1.f, 1.f};

        ImGui::PushStyleColor(ImGuiCol_Text, couleur_texte);

        // Dame
        if (ImGui::Button("Dame", ImVec2(100, 50)))
        {
            pieceMap[pos_pion_a_promouvoir.x][pos_pion_a_promouvoir.y] = std::make_unique<Reine>(couleur_pion, "Q");
            promo_en_cours                                             = false;
            tour_actuel                                                = (tour_actuel == Color::blanc) ? Color::noir : Color::blanc;
            ImGui::CloseCurrentPopup();
        }

        // Tour
        ImGui::SameLine();
        if (ImGui::Button("Tour", ImVec2(100, 50)))
        {
            pieceMap[pos_pion_a_promouvoir.x][pos_pion_a_promouvoir.y] = std::make_unique<Tour>(couleur_pion, "T");
            promo_en_cours                                             = false;
            tour_actuel                                                = (tour_actuel == Color::blanc) ? Color::noir : Color::blanc;
            ImGui::CloseCurrentPopup();
        }

        // Fou
        ImGui::SameLine();
        if (ImGui::Button("Fou", ImVec2(100, 50)))
        {
            pieceMap[pos_pion_a_promouvoir.x][pos_pion_a_promouvoir.y] = std::make_unique<Fou>(couleur_pion, "F");
            promo_en_cours                                             = false;
            tour_actuel                                                = (tour_actuel == Color::blanc) ? Color::noir : Color::blanc;
            ImGui::CloseCurrentPopup();
        }

        // Cavalier
        ImGui::SameLine();
        if (ImGui::Button("Cavalier", ImVec2(100, 50)))
        {
            pieceMap[pos_pion_a_promouvoir.x][pos_pion_a_promouvoir.y] = std::make_unique<Cavalier>(couleur_pion, "C");
            promo_en_cours                                             = false;
            tour_actuel                                                = (tour_actuel == Color::blanc) ? Color::noir : Color::blanc;
            ImGui::CloseCurrentPopup();
        }

        ImGui::PopStyleColor();
        ImGui::EndPopup();
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
            // Vérification de promotion pour un pion
            if (pieceMap[i][j]->label() == "P" && ((pieceMap[i][j]->getColor() == Color::blanc && i == 0) || (pieceMap[i][j]->getColor() == Color::noir && i == 7)))
            {
                promo_en_cours        = true;
                pos_pion_a_promouvoir = {i, j};
                // Ne pas changer de tour tant que la promotion n'est pas effectuée
            }
            else
            {
                tour_actuel = (tour_actuel == Color::blanc) ? Color::noir : Color::blanc;
            }
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
    gerer_promotion();
}

void Board::initializeBoard3D(const std::string& meshPath, const std::string& meshName)
{
    path = meshPath;
    name = meshName;

    // Initialiser le modèle du plateau
    board3D.load_mesh(path, name);
    board3D.setup_buffers();

    // Initialiser toutes les pièces 3D
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (pieceMap[i][j] != nullptr)
            {
                std::string pieceType;
                std::string colorSuffix = (pieceMap[i][j]->getColor() == Color::noir) ? "2" : "";

                // Déterminer le type de pièce
                if (pieceMap[i][j]->label() == "P")
                    pieceType = "pawn/pawn";
                else if (pieceMap[i][j]->label() == "T")
                    pieceType = "rook/tower";
                else if (pieceMap[i][j]->label() == "C")
                    pieceType = "knight/cavalier";
                else if (pieceMap[i][j]->label() == "F")
                    pieceType = "bishop/fou";
                else if (pieceMap[i][j]->label() == "Q")
                    pieceType = "queen/queen";
                else if (pieceMap[i][j]->label() == "K")
                    pieceType = "king/king";

                // Charger le modèle approprié
                pieceMap[i][j]->model3D.load_mesh(pieceType + colorSuffix + ".obj", pieceType.substr(0, pieceType.find("/")));
                pieceMap[i][j]->model3D.setup_buffers();
            }
        }
    }
}

void Board::render3D(glmax::Shader& shader)
{
    // Dessiner le plateau avec une échelle réduite si nécessaire
    shader.use();
    glm::mat4 boardTransform = glm::mat4(1.0f);
    // Ajustez cette valeur si le plateau est trop grand
    boardTransform = glm::scale(boardTransform, glm::vec3(0.9f, 0.9f, 0.9f));
    shader.set_uniform_matrix_4fv("model", boardTransform);
    board3D.render(shader);
}

void Board::render_pieces3D(glmax::Shader& shader)
{
    // Augmenter l'échelle des pièces à 0.3
    float scale      = 0.9f; // Échelle des modèles augmentée
    float squareSize = 6.0f; // Taille d'une case en unités 3D

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (pieceMap[i][j] != nullptr)
            {
                // Calculer la position 3D
                glm::mat4 transform = glm::mat4(1.0f);
                // Ajuster la position en fonction de l'échelle du plateau
                transform = glm::translate(transform, glm::vec3(j * squareSize - 21.0f, 0.0f, i * squareSize - 21.0f));
                transform = glm::scale(transform, glm::vec3(scale, scale, scale));

                // Appliquer la transformation et rendre la pièce
                shader.set_uniform_matrix_4fv("model", transform);
                pieceMap[i][j]->model3D.render(shader);
            }
        }
    }
}