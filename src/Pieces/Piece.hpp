#pragma once
#include <iostream>
enum class Color {
    noir,
    blanc

};

class Board;
class Piece {
public:
    Piece(const Piece&)            = delete;
    Piece(Piece&&)                 = delete;
    Piece& operator=(const Piece&) = delete;
    Piece& operator=(Piece&&)      = delete;

    virtual ~Piece() = default;
    virtual void        move();
    virtual std::string label() = 0;
    Color               getColor();
    void                setColor(Color color);

private:
    int   id{};
    Color color{};
};
