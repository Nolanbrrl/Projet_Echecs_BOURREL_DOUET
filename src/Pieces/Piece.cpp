#include "Piece.hpp"
#include "Board.hpp"

Color Piece::getColor()
{
    return color;
}

void Piece::setColor(Color color)
{
    this->color = color;
}