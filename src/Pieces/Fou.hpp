#include "Piece.hpp"

class Fou : public Piece {
public:
    Fou(Color color, std::string label);
    ~Fou() override = default;
    std::string label() override;
};