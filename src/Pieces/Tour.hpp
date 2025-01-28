#include "Piece.hpp"

class Tour : public Piece {
public:
    Tour(Color color, std::string label);
    ~Tour() override = default;
    std::string label() override;

    void move();

private:
    int id{};
};