#include "Reine.hpp"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Board.hpp"
#include "Model3D.hpp"
#include "Shader.hpp"
#include "utils.hpp"


static void move();

std::string Reine::label()
{
    return "Q";
}

void Reine::setLabel(std::string label)
{
    this->label() = label;
};

std::string Reine::getLabel()
{
    return this->label();
};

Reine::Reine(Color color, std::string label)
{
    this->setColor(color);
    this->setLabel(label);
};

std::vector<Position> Reine::list_all_possible_moves(Board const& board, Position current_position)
{
    std::vector<Position>            possible_moves{};
    std::vector<std::pair<int, int>> directions = {
        {1, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {-1, 1}, {1, 1}, {-1, -1}
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
            if (board.pieceMap[next_position.x][next_position.y] != nullptr && (board.pieceMap[next_position.x][next_position.y]->getColor() != getColor()))
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

void Reine::draw3D(Color color)
{
    if (color == Color::noir)
    {
        queenModel.load_mesh(path_noir, name);
    }
    else
    {
        queenModel.load_mesh(path_blanc, name);
    }
    queenModel.setup_buffers();
}

void Reine::render3D(glmax::Shader& shader)
{
    queenModel.render(shader);
}