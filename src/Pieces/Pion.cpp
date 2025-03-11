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
    int                   direction = (getColor() == Color::noir) ? 1 : -1; // Noir avance vers le bas, Blanc vers le haut

    int start_row = (getColor() == Color::noir) ? 1 : 6; // Ligne de départ des pions

    // 1️⃣ **Avancer d'une case si elle est vide**
    Position one_step = {current_position.x + direction, current_position.y};
    if (board.pieceMap[one_step.x][one_step.y] == nullptr) // Vérifie si la case est libre
    {
        possible_moves.push_back(one_step);

        // 2️⃣ **Avancer de 2 cases si c'est le premier mouvement**
        Position two_steps = {current_position.x + 2 * direction, current_position.y};
        if (current_position.x == start_row && board.pieceMap[two_steps.x][two_steps.y] == nullptr)
        {
            possible_moves.push_back(two_steps);
        }
    }

    // 3️⃣ **Capturer en diagonale**
    for (int dy : {-1, 1}) // Vérifie les diagonales gauche (-1) et droite (+1)
    {
        Position diagonal_position = {current_position.x + direction, current_position.y + dy};
        if (diagonal_position.y >= 0 && diagonal_position.y < 8 && board.pieceMap[diagonal_position.x][diagonal_position.y] != nullptr)
        {
            if (board.pieceMap[diagonal_position.x][diagonal_position.y]->getColor() != getColor())
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

            if (board.pieceMap[passant_position.x][passant_position.y] == nullptr)
            {
                possible_moves.push_back(passant_position);
            }
        }
    }

    return possible_moves;
}
