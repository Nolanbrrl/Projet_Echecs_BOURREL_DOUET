// #pragma once
// #include <imgui.h>
// #include <winscard.h>
// #include <array>
// #include <iostream>
// #include <memory>
// #include <optional>
// #include <unordered_map>
// #include "ImportObj.hpp"
// #include "Pieces/Piece.hpp"

// class Board {
// private:
//     std::array<std::array<int, 8>, 8> tileMap;

// public:
//     Board();

//     void                                                 draw(int argc, char** argv);
//     void                                                 initializeBoard();
//     void                                                 drawBoard();
//     void                                                 drawPieces();
//     void                                                 handleClick(int i, int j);
//     void                                                 checkGameOver();
//     std::array<std::array<std::unique_ptr<Piece>, 8>, 8> pieceMap{};
//     std::vector<Position>                                possible_moves;
//     std::optional<Position>                              selected_piece_position;
//     bool                                                 is_inside_board(Position pos) const;
//     bool                                                 is_enemy_piece(Position pos, Color color) const;
//     std::vector<std::unique_ptr<Piece>>                  cimetiere_piece_noire;
//     std::vector<std::unique_ptr<Piece>>                  cimetiere_piece_blanche;
//     bool                                                 partie_terminee = false;
//     void                                                 resetBoard();
//     Color                                                tour_actuel = Color::blanc;
//     std::optional<Position>                              pion_pour_prise_en_passant;
//     void                                                 drawBorders();
//     void                                                 drawTiles();
//     void                                                 drawBorderCube(float x, float y, float z, float scaleX, float scaleY, float scaleZ, const ImVec4& color);
// };