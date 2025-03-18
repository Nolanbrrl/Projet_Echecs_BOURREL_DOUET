#include <imgui.h>
#include <iostream>
#include "Board.hpp"
#include "quick_imgui/quick_imgui.hpp"

int main(int argc, char** argv)
{
    Board board;
    board.draw(argc, argv);
}