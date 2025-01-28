#include <iostream>
#include "Piece.hpp"

class Pion : public Piece {
public:
    Pion(Color color, std::string label);
    ~Pion() override = default;
    std::string label() override;

private:
};