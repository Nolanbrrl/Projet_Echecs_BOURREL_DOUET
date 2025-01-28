#include "Piece.hpp"

class Cavalier : public Piece {
public:
    Cavalier(Color color, std::string label);
    ~Cavalier() override = default; // kekonafé?
    std::string label() override;
};