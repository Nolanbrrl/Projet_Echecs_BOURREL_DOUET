#include <iostream>

class Piece {
public:
    virtual ~Piece() = default;
    void                move();
    virtual std::string label() = 0;

private:
    int  id{};
    bool camp{};
};
