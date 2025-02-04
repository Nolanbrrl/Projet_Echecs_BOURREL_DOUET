#pragma once
#include "Piece.hpp"

class Tour : public Piece {
public:
    // Tour() = default;
    Tour(Color color, std::string label);
    // ~Tour() override = default;
    void        setLabel(std::string label);
    std::string getLabel();

private:
    std::string label() override;
};