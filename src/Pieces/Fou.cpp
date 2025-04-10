#include "Fou.hpp"
#include <imgui.h>
#include <glm/glm.hpp>
#include "Board.hpp"
#include "Model3D.hpp"
#include "Shader.hpp"
#include "utils.hpp"

static void move();

std::string Fou::label()
{
    return "F";
}

void Fou::setLabel(std::string label)
{
    this->label() = label;
};

std::string Fou::getLabel()
{
    return this->label();
};

Fou::Fou(Color color, std::string label)
{
    this->setColor(color);
    this->setLabel(label);
};

std::vector<Position> Fou::list_all_possible_moves(Board const& board, Position current_position)
{
    std::vector<Position>            possible_moves{};
    std::vector<std::pair<int, int>> directions = {
        {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
    };

    for (const auto& direction : directions)
    {
        int      i             = 1;
        Position next_position = {
            .x = current_position.x + i * direction.first,
            .y = current_position.y + i * direction.second
        };

        while (is_move_valid(board, next_position, getColor()))
        {
            add_move_if_valid(next_position, possible_moves, board, getColor());
            if (board.pieceMap[next_position.x][next_position.y] != nullptr && board.pieceMap[next_position.x][next_position.y]->getColor() != getColor())
            {
                break;
            }
            i++;
            next_position = {
                .x = current_position.x + i * direction.first,
                .y = current_position.y + i * direction.second
            };
        }
    }

    return possible_moves;
}

void Fou::draw3D(Color color)
{
    if (color == Color::blanc)
    {
        bishopModel.load_mesh(path_blanc, name);
    }
    else
    {
        bishopModel.load_mesh(path_noir, name);
    }
    bishopModel.setup_buffers();
}

void Fou::render3D(glmax::Shader& shader)
{
    bishopModel.render(shader);
}