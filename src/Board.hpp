#pragma once
#include <winscard.h>
#include <array>
#include <iostream>
#include <memory>
#include <optional>
#include "Pieces/Piece.hpp"

class Board {
private:
public:
    Board();

    void                                                 draw();
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> pieceMap{};
    std::vector<Position>                                possible_moves;
    std::optional<Position>                              selected_piece_position;
    bool                                                 is_inside_board(Position pos) const;
    bool                                                 is_enemy_piece(Position pos, Color color) const;
};