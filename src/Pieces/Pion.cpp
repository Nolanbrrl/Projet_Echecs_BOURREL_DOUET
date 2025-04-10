#include "Pion.hpp"
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
    int                   direction = (getColor() == Color::noir) ? 1 : -1;
    int                   start_row = (getColor() == Color::noir) ? 1 : 6;
    Color                 color     = getColor();

    Position one_step = {current_position.x + direction, current_position.y};
    if (one_step.x >= 0 && one_step.x < 8)
    {
        if (board.pieceMap[one_step.x][one_step.y] == nullptr && is_move_valid(board, one_step, color))
        {
            possible_moves.push_back(one_step);

            Position two_steps = {current_position.x + 2 * direction, current_position.y};
            if (two_steps.x >= 0 && two_steps.x < 8)
            {
                if (current_position.x == start_row && board.pieceMap[two_steps.x][two_steps.y] == nullptr && is_move_valid(board, two_steps, color))
                {
                    possible_moves.push_back(two_steps);
                }
            }
        }
    }

    for (int dy : {-1, 1})
    {
        Position diagonal_position = {current_position.x + direction, current_position.y + dy};
        if (diagonal_position.x >= 0 && diagonal_position.x < 8 && diagonal_position.y >= 0 && diagonal_position.y < 8)
        {
            if (is_move_valid(board, diagonal_position, color) && board.pieceMap[diagonal_position.x][diagonal_position.y] != nullptr)
            {
                possible_moves.push_back(diagonal_position);
            }
        }
    }

    if (board.pion_pour_prise_en_passant.has_value())
    {
        Position passant_pion = board.pion_pour_prise_en_passant.value();
        if (std::abs(passant_pion.y - current_position.y) == 1 && passant_pion.x == current_position.x)
        {
            Position passant_position = {current_position.x + direction, passant_pion.y};
            if (passant_position.x >= 0 && passant_position.x < 8)
            {
                if (board.pieceMap[passant_position.x][passant_position.y] == nullptr && is_move_valid(board, passant_position, color))
                {
                    possible_moves.push_back(passant_position);
                }
            }
        }
    }

    return possible_moves;
}

void Pion::draw3D(Color color)
{
    if (color == Color::blanc)
    {
        pawnModel.load_mesh(path_blanc, name);
    }
    else
    {
        pawnModel.load_mesh(path_noir, name);
    }
    pawnModel.setup_buffers();
}

void Pion::render3D(glmax::Shader& shader)
{
    pawnModel.render(shader);
}