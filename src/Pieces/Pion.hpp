#include <iostream>
#include "Piece.hpp"

class Pion : public Piece {
public:
    virtual ~Pion() = default;
    std::string label() override;

private:
};