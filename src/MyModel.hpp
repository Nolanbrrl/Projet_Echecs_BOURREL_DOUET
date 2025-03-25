#include <iostream>
#include "Buffers/EBO.hpp"
#include "Buffers/VAO.hpp"
#include "Buffers/VBO.hpp"
#include "Mesh.hpp"

class MyModel {
public:
    void load_mesh(const std::string& path, const std::string& name); // 1
    void setup_buffers();                                             // 2
    void render(glmax::Shader& shader) const;                         // 3

private:
    // single mesh
    glmax::Mesh m_mesh;
    //
    // Buffers
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
};