#include "Reine.hpp"
#include "Board.hpp"
#include "utils.hpp"

static void move();

std::string Reine::label()
{
    return "Q";
}

void Reine::setLabel(std::string label)
{
    this->label() = label;
};

std::string Reine::getLabel()
{
    return this->label();
};

Reine::Reine(Color color, std::string label)
{
    this->setColor(color);
    this->setLabel(label);
};

std::vector<Position> Reine::list_all_possible_moves(Board const& board, Position current_position)
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
    int      m{1};
    Position Next_position5 = {.x = current_position.x + m, .y = current_position.y - m};
    while (is_move_valid(board, (Next_position5), getColor()))
    {
        add_move_if_valid(Next_position5, possible_moves, board, getColor());
        i++;
    }
    int      n{1};
    Position Next_position6 = {.x = current_position.x - n, .y = current_position.y + n};
    while (is_move_valid(board, (Next_position6), getColor()))
    {
        add_move_if_valid(Next_position6, possible_moves, board, getColor());
        i++;
    }
    int      o{1};
    Position Next_position7 = {.x = current_position.x + o, .y = current_position.y + o};
    while (is_move_valid(board, (Next_position7), getColor()))
    {
        add_move_if_valid(Next_position7, possible_moves, board, getColor());
        i++;
    }
    int      p{1};
    Position Next_position8 = {.x = current_position.x - p, .y = current_position.y - p};
    while (is_move_valid(board, (Next_position8), getColor()))
    {
        add_move_if_valid(Next_position8, possible_moves, board, getColor());
        i++;
    }
    return possible_moves;
};
