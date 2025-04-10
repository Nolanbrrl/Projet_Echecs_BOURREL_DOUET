#include "Roi.hpp"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Board.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include "utils.hpp"

static void move();

std::string Roi::label()
{
    return "K";
}

void Roi::setLabel(std::string label)
{
    this->label() = label;
};

std::string Roi::getLabel()
{
    return this->label();
};

Roi::Roi(Color color, std::string label)
{
    this->setColor(color);
    this->setLabel(label);
};

std::vector<Position> Roi::list_all_possible_moves(Board const& board, Position current_position)
{
    std::vector<Position> possible_moves{};
    Position              Next_position = {.x = current_position.x + 1, .y = current_position.y + 1};
    if (is_move_valid(board, (Next_position), getColor()))
    {
        add_move_if_valid(Next_position, possible_moves, board, getColor());
    }
    Position Next_position2 = {.x = current_position.x, .y = current_position.y + 1};
    if (is_move_valid(board, (Next_position2), getColor()))
    {
        add_move_if_valid(Next_position2, possible_moves, board, getColor());
    }
    Position Next_position3 = {.x = current_position.x - 1, .y = current_position.y + 1};
    if (is_move_valid(board, (Next_position3), getColor()))
    {
        add_move_if_valid(Next_position3, possible_moves, board, getColor());
    }
    Position Next_position4 = {.x = current_position.x - 1, .y = current_position.y};
    if (is_move_valid(board, (Next_position4), getColor()))
    {
        add_move_if_valid(Next_position4, possible_moves, board, getColor());
    }
    Position Next_position5 = {.x = current_position.x - 1, .y = current_position.y - 1};
    if (is_move_valid(board, (Next_position5), getColor()))
    {
        add_move_if_valid(Next_position5, possible_moves, board, getColor());
    }
    Position Next_position6 = {.x = current_position.x, .y = current_position.y - 1};
    if (is_move_valid(board, (Next_position6), getColor()))
    {
        add_move_if_valid(Next_position6, possible_moves, board, getColor());
    }
    Position Next_position7 = {.x = current_position.x + 1, .y = current_position.y - 1};
    if (is_move_valid(board, (Next_position7), getColor()))
    {
        add_move_if_valid(Next_position7, possible_moves, board, getColor());
    }
    Position Next_position8 = {.x = current_position.x + 1, .y = current_position.y};
    if (is_move_valid(board, (Next_position8), getColor()))
    {
        add_move_if_valid(Next_position8, possible_moves, board, getColor());
    }
    return possible_moves;
};

void Roi::draw3D(Color color)
{
    if (color == Color::blanc)
    {
        kingModel.load_mesh(path_blanc, name);
    }
    else
    {
        kingModel.load_mesh(path_noir, name);
    }
    kingModel.setup_buffers();
}

void Roi::render3D(glmax::Shader& shader)
{
    kingModel.render(shader);
}