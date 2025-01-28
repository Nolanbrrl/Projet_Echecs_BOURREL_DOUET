#include "Piece.hpp"

class Tour : public Piece {
public:
    void        move();
    std::string label = "T";
    Color       getCamp()
    {
        return color;
    };
    bool setCamp();

private:
    int   id{};
    Color color{};
};