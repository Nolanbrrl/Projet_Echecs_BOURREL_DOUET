#pragma once
#include "Piece.hpp"

class Reine : public Piece {
public:
    // Reine() = default;
    Reine(Color color, std::string label);
    // ~Reine() override = default;
    void        setLabel(std::string label);
    std::string getLabel();

private:
    std::string           label() override;
    std::vector<Position> list_all_possible_moves(Board const&, Position current_position) override;
};