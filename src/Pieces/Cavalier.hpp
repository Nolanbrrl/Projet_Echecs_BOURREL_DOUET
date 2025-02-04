#pragma once
#include "Piece.hpp"
class Cavalier : public Piece {
public:
    // Cavalier() = default;
    Cavalier(Color color, std::string label);
    // ~Cavalier() override = default;
    void        setLabel(std::string label);
    std::string getLabel();

private:
    std::string label() override;
};