#pragma once
#include <imgui.h>
#include <winscard.h>
#include <array>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include "Model3D.hpp"
#include "Pieces/Piece.hpp"

class Board {
private:
    std::array<std::array<int, 8>, 8> tileMap;
    bool                              promo_en_cours = false;
    Position                          pos_pion_a_promouvoir;

    void gerer_promotion();

public:
    Board();

    // void                                                 draw(int argc, char** argv);
    void                                                 initializeBoard();
    void                                                 drawBoard();
    void                                                 drawPieces();
    void                                                 handleClick(int i, int j);
    void                                                 checkGameOver();
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> pieceMap{};
    std::vector<Position>                                possible_moves;
    std::optional<Position>                              selected_piece_position;
    bool                                                 is_inside_board(Position pos) const;
    bool                                                 is_enemy_piece(Position pos, Color color) const;
    std::vector<std::unique_ptr<Piece>>                  cimetiere_piece_noire;
    std::vector<std::unique_ptr<Piece>>                  cimetiere_piece_blanche;
    bool                                                 partie_terminee = false;
    void                                                 resetBoard();
    Color                                                tour_actuel = Color::blanc;
    std::optional<Position>                              pion_pour_prise_en_passant;
    Model3D                                              board3D;
    std::string                                          path = "../../assets/models/board/board.obj";
    std::string                                          name = "board";
    void                                                 render3D(glmax::Shader& shader);
    void                                                 render_pieces3D(glmax::Shader& shader);
    void                                                 initializeBoard3D(const std::string& meshPath, const std::string& meshName);
};