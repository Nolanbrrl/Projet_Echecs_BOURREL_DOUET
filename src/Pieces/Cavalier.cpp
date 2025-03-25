// #include "Cavalier.hpp"
// #include <utility>
// #include "Board.hpp"
// #include "Piece.hpp"
// #include "utils.hpp"

// static void move();

// std::string Cavalier::label()
// {
//     return "C";
// };

// void Cavalier::setLabel(std::string label)
// {
//     this->label() = label;
// };

// std::string Cavalier::getLabel()
// {
//     return this->label();
// };

// Cavalier::Cavalier(Color color, std::string label)
// {
//     this->setColor(color);
//     this->setLabel(label);
// };

// // bool Cavalier::isMovePossible(Board board)
// // {
// //     return true;
// // };

// std::vector<Position> Cavalier::list_all_possible_moves(Board const& board, Position current_position)
// {
//     std::vector<Position> possible_moves{};

//     add_move_if_valid({.x = current_position.x + 2, .y = current_position.y + 1}, possible_moves, board, getColor());
//     add_move_if_valid({.x = current_position.x + 2, .y = current_position.y - 1}, possible_moves, board, getColor());
//     add_move_if_valid({.x = current_position.x + 1, .y = current_position.y - 2}, possible_moves, board, getColor());
//     add_move_if_valid({.x = current_position.x - 1, .y = current_position.y - 2}, possible_moves, board, getColor());
//     add_move_if_valid({.x = current_position.x - 2, .y = current_position.y - 1}, possible_moves, board, getColor());
//     add_move_if_valid({.x = current_position.x - 2, .y = current_position.y + 1}, possible_moves, board, getColor());
//     add_move_if_valid({.x = current_position.x - 1, .y = current_position.y + 2}, possible_moves, board, getColor());
//     add_move_if_valid({.x = current_position.x + 1, .y = current_position.y + 2}, possible_moves, board, getColor());

//     return possible_moves;
// };