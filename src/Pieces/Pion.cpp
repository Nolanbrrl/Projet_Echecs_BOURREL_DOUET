#include "Pion.hpp"
#include <iostream>
#include "Board.hpp"

static void move();

std::string Pion::label()
{
    return "P";
}

void Pion::setLabel(std::string label)
{
    this->label() = label;
};

std::string Pion::getLabel()
{
    return this->label();
};

Pion::Pion(Color color, std::string label)
{
    this->setColor(color);
    this->setLabel(label);
};
