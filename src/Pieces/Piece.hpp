#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Model3D.hpp"
#include "Shader.hpp"

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

    explicit Piece(Color color)
        : color(color) {}
    virtual ~Piece()                                                                               = default;
    virtual std::vector<Position> list_all_possible_moves(Board const&, Position current_position) = 0;
    virtual std::string           label()                                                          = 0;
    Color                         getColor();
    void                          setColor(Color color);
    void                          move(Board&, Position current_position, Position next_position);
    virtual void                  draw3D(Color color)             = 0;
    virtual void                  render3D(glmax::Shader& shader) = 0;
    Model3D                       model3D;

protected:
    std::string path_noir;
    std::string path_blanc;
    std::string name;

private:
    int   id{};
    Color color{};
};
