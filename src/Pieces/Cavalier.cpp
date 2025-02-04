#include "Cavalier.hpp"
#include <utility>
#include "Board.hpp"

static void move();

std::string Cavalier::label()
{
    return "C";
}

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
