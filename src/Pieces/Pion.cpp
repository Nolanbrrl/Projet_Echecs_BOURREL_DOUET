#include "Pion.hpp"
#include <iostream>
#include "Board.hpp"
#include "Piece.hpp"
#include "utils.hpp"

static void move();

std::string Pion::label()
{
    return "P";
}

void Pion::setLabel(std::string label)
{
    this->label() = label;
};

std::string Pion::getLabel()
{
    return this->label();
};

Pion::Pion(Color color, std::string label)
{
    this->setColor(color);
    this->setLabel(label);
};

std::vector<Position> Pion::list_all_possible_moves(Board const& board, Position current_position)
{
    std::vector<Position> possible_moves{};
    Position              next_position;

    if (getColor() == Color::noir)
    {
        next_position = {.x = current_position.x, .y = current_position.y - 1};
        if (is_move_valid(board, next_position, getColor()))
        {
            add_move_if_valid(next_position, possible_moves, board, getColor());
        }
    }
    else
    {
        next_position = {.x = current_position.x, .y = current_position.y + 1};
        if (is_move_valid(board, next_position, getColor()))
        {
            add_move_if_valid(next_position, possible_moves, board, getColor());
        }
    }

    return possible_moves;
}