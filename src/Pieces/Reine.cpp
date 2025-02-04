#include "Reine.hpp"
#include "Board.hpp"

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
