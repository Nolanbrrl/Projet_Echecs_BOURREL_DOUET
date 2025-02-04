
#pragma once
#include <iostream>
#include "Piece.hpp"

class Pion : public Piece {
public:
    // Pion() = default;
    Pion(Color color, std::string label);
    // ~Pion() override = default;
    void        setLabel(std::string label);
    std::string getLabel();

private:
    std::string label() override;
};