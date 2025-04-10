#include "Tour.hpp"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Board.hpp"
#include "utils.hpp"


static void move();

std::string Tour::label()
{
    return "T";
}

void Tour::setLabel(std::string label)
{
    this->label() = label;
};

std::string Tour::getLabel()
{
    return this->label();
};

Tour::Tour(Color color, std::string label)
{
    this->setColor(color);
    this->setLabel(label);
};

std::vector<Position> Tour::list_all_possible_moves(Board const& board, Position current_position)
{
    std::vector<Position>            possible_moves{};
    std::vector<std::pair<int, int>> directions = {
        {1, 0}, {-1, 0}, {0, -1}, {0, 1}
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
                break; // Stop if an enemy piece is encountered
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

void Tour::draw3D(Color color)
{
    if (color == Color::blanc)
    {
        rookModel.load_mesh(path_blanc, name);
    }
    else
    {
        rookModel.load_mesh(path_noir, name);
    }
    rookModel.setup_buffers();
}

void Tour::render3D(glmax::Shader& shader)
{
    rookModel.render(shader);
}