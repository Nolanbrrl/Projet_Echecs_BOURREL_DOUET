#pragma once
#include "Piece.hpp"

class Fou : public Piece {
public:
    // Fou() = default;
    Fou(Color color, std::string label);
    // ~Fou() override = default;
    void        setLabel(std::string label);
    std::string getLabel();

private:
    std::string label() override;
};