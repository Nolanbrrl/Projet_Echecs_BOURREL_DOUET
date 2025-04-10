#pragma once
#include "Model3D.hpp"
#include "Piece.hpp"

class Tour : public Piece {
public:
    // Tour() = default;
    Tour(Color color, std::string label);
    // ~Tour() override = default;
    void        setLabel(std::string label);
    std::string getLabel();
    explicit Tour(Color color)
        : Piece(color)
    {
        path_noir  = "../../assets/models/rook/tower2.obj";
        path_blanc = "../../assets/models/rook/tower.obj";
        name       = "rook";
    }
    void draw3D(Color color) override;
    void render3D(glmax::Shader& shader) override;

private:
    std::string           label() override;
    std::vector<Position> list_all_possible_moves(Board const&, Position current_position) override;
    Model3D               rookModel;
};