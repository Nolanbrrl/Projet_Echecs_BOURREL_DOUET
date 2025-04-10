
#pragma once
#include <iostream>
#include "Model3D.hpp"
#include "Piece.hpp"

class Pion : public Piece {
public:
    Pion(Color color, std::string label);
    void        setLabel(std::string label);
    std::string getLabel();
    explicit Pion(Color color)
        : Piece(color)
    {
        path_noir  = "../../assets/models/pawn/pawn2.obj";
        path_blanc = "../../assets/models/pawn/pawn.obj";
        name       = "pawn";
    }
    void draw3D(Color color) override;
    void render3D(glmax::Shader& shader) override;

private:
    std::string           label() override;
    std::vector<Position> list_all_possible_moves(Board const&, Position current_position) override;
    Model3D               pawnModel;
};