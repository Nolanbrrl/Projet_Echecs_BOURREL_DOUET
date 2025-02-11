#include "Tour.hpp"
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
