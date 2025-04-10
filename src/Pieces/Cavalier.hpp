#pragma once
#include "Model3D.hpp"
#include "Piece.hpp"

class Cavalier : public Piece {
public:
    Cavalier(Color color, std::string label);
    void        setLabel(std::string label);
    std::string getLabel();
    explicit Cavalier(Color color)
        : Piece(color)
    {
        path_noir  = "../../assets/models/knight/cavalier2.obj";
        path_blanc = "../../assets/models/knight/cavalier.obj";
        name       = "knight";
    }
    void draw3D(Color color) override;
    void render3D(glmax::Shader& shader) override;

private:
    std::string           label() override;
    std::vector<Position> list_all_possible_moves(Board const&, Position current_position) override;
    Model3D               knightModel;
};