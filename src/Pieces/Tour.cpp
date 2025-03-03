#include "Tour.hpp"
#include "Board.hpp"
#include "utils.hpp"

static void move();

std::string Tour::label()
{
    return "T";
}

void Tour::setLabel(std::string label)
{
    this->label() = label;
};

std::string Tour::getLabel()
{
    return this->label();
};

Tour::Tour(Color color, std::string label)
{
    this->setColor(color);
    this->setLabel(label);
};

std::vector<Position> Tour::list_all_possible_moves(Board const& board, Position current_position)
{
    std::vector<Position> possible_moves{};
    int                   i{1};
    Position              Next_position = {.x = current_position.x + i, .y = current_position.y};
    while (is_move_valid(board, (Next_position), getColor()))
    {
        add_move_if_valid(Next_position, possible_moves, board, getColor());
        i++;
    }
    int      j{1};
    Position Next_position2 = {.x = current_position.x - j, .y = current_position.y};
    while (is_move_valid(board, (Next_position2), getColor()))
    {
        add_move_if_valid(Next_position2, possible_moves, board, getColor());
        i++;
    }
    int      k{1};
    Position Next_position3 = {.x = current_position.x, .y = current_position.y - k};
    while (is_move_valid(board, (Next_position3), getColor()))
    {
        add_move_if_valid(Next_position3, possible_moves, board, getColor());
        i++;
    }
    int      l{1};
    Position Next_position4 = {.x = current_position.x, .y = current_position.y + l};
    while (is_move_valid(board, (Next_position4), getColor()))
    {
        add_move_if_valid(Next_position4, possible_moves, board, getColor());
        i++;
    }
    return possible_moves;
};
