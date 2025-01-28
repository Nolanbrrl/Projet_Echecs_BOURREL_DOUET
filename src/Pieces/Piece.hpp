#include <iostream>

class Piece {
public:
    virtual ~Piece() = default;
    void                move();
    virtual std::string label() = 0;
    bool                getCamp()
    {
        return camp;
    };
    bool setCamp()
    {
        // à voir
    }

private:
    int  id{};
    bool camp{};
};
