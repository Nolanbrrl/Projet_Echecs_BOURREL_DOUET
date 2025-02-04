#include "Roi.hpp"
#include "Board.hpp"

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
