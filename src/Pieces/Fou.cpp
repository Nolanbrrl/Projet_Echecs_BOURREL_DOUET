#include "Fou.hpp"
#include "Board.hpp"
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
