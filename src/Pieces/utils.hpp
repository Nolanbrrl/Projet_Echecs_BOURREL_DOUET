#pragma once
#include <iostream>
#include <vector>
#include "Board.hpp"
#include "Piece.hpp"

static bool is_move_valid(Board const& board, Position pos_future, Color color)
{
    if (pos_future.x < 0 || pos_future.x > 7 || pos_future.y < 0 || pos_future.y > 7)
    {
        return false;
    }
    if (board.pieceMap[pos_future.x][pos_future.y] != nullptr && color == board.pieceMap[pos_future.x][pos_future.y]->getColor())
    {
        return false;
    }
    if (board.pieceMap[pos_future.x][pos_future.y] != nullptr && color != board.pieceMap[pos_future.x][pos_future.y]->getColor())
    {
        return true;
    }
    return true;
}

static void add_move_if_valid(Position pos_future, std::vector<Position>& possible_moves, Board const& board, Color color)
{
    if (is_move_valid(board, pos_future, color))
    {
        possible_moves.push_back(pos_future);
    }
}
