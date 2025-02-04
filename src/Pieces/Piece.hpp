#pragma once
#include <iostream>
enum class Color {
    noir,
    blanc

};
class Piece {
public:
    virtual ~Piece() = default;
    void                move();
    virtual std::string label() = 0;
    Color               getColor();
    void                setColor(Color color);

private:
    int   id{};
    Color color{};
};
