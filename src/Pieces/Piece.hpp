#pragma once
#include <iostream>
#include <vector>
enum class Color {
    noir,
    blanc

};

struct Position {
    int x;
    int y;

    bool operator==(Position const& pos) const = default;
};

class Board;
class Piece {
public:
    Piece()                        = default;
    Piece(const Piece&)            = delete;
    Piece(Piece&&)                 = delete;
    Piece& operator=(const Piece&) = delete;
    Piece& operator=(Piece&&)      = delete;

    virtual ~Piece()                                                                               = default;
    virtual std::vector<Position> list_all_possible_moves(Board const&, Position current_position) = 0;
    virtual std::string           label()                                                          = 0;
    Color                         getColor();
    void                          setColor(Color color);

private:
    int   id{};
    Color color{};
};
