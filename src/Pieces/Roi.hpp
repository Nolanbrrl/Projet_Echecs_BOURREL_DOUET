#include "Piece.hpp"

class Roi : public Piece {
public:
    Roi(Color color, std::string label);
    ~Roi() override = default;
    std::string label() override;
};