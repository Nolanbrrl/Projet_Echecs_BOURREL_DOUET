#pragma once
#include "Model3D.hpp"
#include "Piece.hpp"

class Reine : public Piece {
public:
    // Reine() = default;
    Reine(Color color, std::string label);
    // ~Reine() override = default;
    void        setLabel(std::string label);
    std::string getLabel();
    explicit Reine(Color color)
        : Piece(color)
    {
        path_noir  = "../../assets/models/queen/queen2.obj";
        path_blanc = "../../assets/models/queen/queen.obj";
        name       = "queen";
    }
    void draw3D(Color color) override;
    void render3D(glmax::Shader& shader) override;

private:
    std::string           label() override;
    std::vector<Position> list_all_possible_moves(Board const&, Position current_position) override;
    Model3D               queenModel;
};