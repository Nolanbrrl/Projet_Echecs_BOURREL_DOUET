#include "Piece.hpp"

class Reine : public Piece {
public:
    Reine(Color color, std::string label);
    ~Reine() override = default;
    std::string label() override;
};