#include "Cavalier.hpp"
#include <imgui.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Board.hpp"
#include "Camera.hpp"
#include "Model3D.hpp"
#include "Shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include "utils.hpp"

static void move();

std::string Cavalier::label()
{
    return "C";
};

void Cavalier::setLabel(std::string label)
{
    this->label() = label;
};

std::string Cavalier::getLabel()
{
    return this->label();
};

Cavalier::Cavalier(Color color, std::string label)
{
    this->setColor(color);
    this->setLabel(label);
};

// bool Cavalier::isMovePossible(Board board)
// {
//     return true;
// };

std::vector<Position> Cavalier::list_all_possible_moves(Board const& board, Position current_position)
{
    std::vector<Position> possible_moves{};

    add_move_if_valid({.x = current_position.x + 2, .y = current_position.y + 1}, possible_moves, board, getColor());
    add_move_if_valid({.x = current_position.x + 2, .y = current_position.y - 1}, possible_moves, board, getColor());
    add_move_if_valid({.x = current_position.x + 1, .y = current_position.y - 2}, possible_moves, board, getColor());
    add_move_if_valid({.x = current_position.x - 1, .y = current_position.y - 2}, possible_moves, board, getColor());
    add_move_if_valid({.x = current_position.x - 2, .y = current_position.y - 1}, possible_moves, board, getColor());
    add_move_if_valid({.x = current_position.x - 2, .y = current_position.y + 1}, possible_moves, board, getColor());
    add_move_if_valid({.x = current_position.x - 1, .y = current_position.y + 2}, possible_moves, board, getColor());
    add_move_if_valid({.x = current_position.x + 1, .y = current_position.y + 2}, possible_moves, board, getColor());

    return possible_moves;
};

void Cavalier::draw3D(Color color)
{
    if (color == Color::blanc)
    {
        knightModel.load_mesh(path_blanc, name);
    }
    else
    {
        knightModel.load_mesh(path_noir, name);
    }
    knightModel.setup_buffers();
}

void Cavalier::render3D(glmax::Shader& shader)
{
    knightModel.render(shader);
}