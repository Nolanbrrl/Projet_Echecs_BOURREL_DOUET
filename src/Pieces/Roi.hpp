#pragma once
#include "Piece.hpp"

class Roi : public Piece {
public:
    // Roi() = default;
    Roi(Color color, std::string label);
    // ~Roi() override = default;
    void        setLabel(std::string label);
    std::string getLabel();

private:
    std::string           label() override;
    std::vector<Position> list_all_possible_moves(Board const&, Position current_position) override;
};