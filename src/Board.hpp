#pragma once
#include <winscard.h>
#include <array>
#include <iostream>
#include <memory>
#include "Pieces/Piece.hpp"

class Board {
private:
public:
    Board();

    void                                                 draw();
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> pieceMap{};
};