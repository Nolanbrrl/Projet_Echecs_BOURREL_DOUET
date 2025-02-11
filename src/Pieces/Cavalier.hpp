#pragma once
#include "Piece.hpp"
class Cavalier : public Piece {
public:
    // Cavalier() = default;
    Cavalier(Color color, std::string label);
    // ~Cavalier() override = default;
    void        setLabel(std::string label);
    std::string getLabel();
    // bool        isMovePossible(Board board);

private:
    std::string           label() override;
    std::vector<Position> list_all_possible_moves(Board const&, Position current_position) override;
};