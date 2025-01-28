#include <iostream>
enum class Color {
    noir,
    blanc

};
class Piece {
public:
    virtual ~Piece() = default;
    void                move();
    virtual std::string label() = 0;
    Color               getCamp()
    {
        return color;
    };
    bool setCamp()
    {
    }

private:
    int   id{};
    Color color{};
};
