#pragma once
#include "Model3D.hpp"
#include "Piece.hpp"

class Fou : public Piece {
public:
    Fou(Color color, std::string label);
    void        setLabel(std::string label);
    std::string getLabel();
    explicit Fou(Color color)
        : Piece(color)
    {
        path_noir  = "../../assets/models/bishop/fou2.obj";
        path_blanc = "../../assets/models/bishop/fou.obj";
        name       = "bishop";
    }
    void draw3D(Color color) override;
    void render3D(glmax::Shader& shader) override;

private:
    std::string           label() override;
    std::vector<Position> list_all_possible_moves(Board const&, Position current_position) override;
    Model3D               bishopModel;
};