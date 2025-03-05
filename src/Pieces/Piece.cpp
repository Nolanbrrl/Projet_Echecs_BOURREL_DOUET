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

void Piece::move(Board& board, Position current_position, Position next_position)
{
    // Vérifie si la case de destination est valide
    if (!board.is_inside_board(next_position))
    {
        std::cout << "Erreur : Position hors du plateau !" << std::endl;
        return; // Sortir si la position est invalide
    }

    // Vérifie si la case de destination est occupée par une pièce alliée
    if (board.pieceMap[next_position.x][next_position.y] != nullptr && board.pieceMap[next_position.x][next_position.y]->getColor() == color)
    {
        std::cout << "Erreur : Vous ne pouvez pas déplacer votre pièce sur une case occupée par une pièce alliée." << std::endl;
        return; // Sortir si la destination est occupée par une pièce alliée
    }

    // Effectuer le déplacement
    board.pieceMap[next_position.x][next_position.y]       = std::move(board.pieceMap[current_position.x][current_position.y]);
    board.pieceMap[current_position.x][current_position.y] = nullptr;
}
