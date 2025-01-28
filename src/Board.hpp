#include <winscard.h>
#include <array>
#include <iostream>
class Board {
private:
public:
    Board();

    void                                      draw();
    std::array<std::array<std::string, 8>, 8> pieceMap{};
};