#include <iostream>
#include "Piece.hpp"

class Pion : public Piece {
public:
    ~Pion() override = default;
    std::string label() override;

private:
};