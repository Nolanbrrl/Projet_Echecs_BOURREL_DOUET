#include <imgui.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Board.hpp"
#include "Camera.hpp"
#include "Model3D.hpp"
#include "Shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "quick_imgui/quick_imgui.hpp"

int main()
{
    int           window_width  = 1280;
    int           window_height = 720;
    glmax::Shader shader;
    glmax::Camera camera{true};
    Board         board;
    //
    Model3D modelPion;  // blanc
    Model3D modelPion2; // noir
    Model3D modelPlateau;
    quick_imgui::loop(
        "Quick ImGui",
        {
            .init                     = [&]() { 
            std::cout << "Init\n";
            shader.load_shader("model.vs.glsl", "model.fs.glsl");
            modelPion.load_mesh("pawn/pawn.obj", "pawn");
            modelPion2.load_mesh("pawn/pawn2.obj", "pawn");
            modelPlateau.load_mesh("board/board.obj", "board");
            modelPion.setup_buffers();
            modelPion2.setup_buffers();
            modelPlateau.setup_buffers(); },
            .loop                     = [&]() {
                glClearColor(0.847f, 0.82f, 0.929f, 1.f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);
            
                glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);
            
                // PLATEAU
                shader.use();
                glm::mat4 model_matrix = glm::mat4(1.0f);
                model_matrix = glm::scale(model_matrix, glm::vec3(0.2f, 0.2f, 0.2f));
                shader.set_uniform_matrix_4fv("model", model_matrix); //c'est la matrice model qui fait le deplacement scale et rotate
                shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
                shader.set_uniform_matrix_4fv("projection", projection);
            
                shader.set_uniform_3fv("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
                shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
                shader.set_uniform_3fv("viewPos", camera.get_position());
            
                modelPlateau.render(shader);

                // PIONS BLANCS
                shader.use();
                glm::mat4 model_matrix2 = glm::mat4(1.0f);
                model_matrix2 = glm::scale(model_matrix2, glm::vec3(0.2f, 0.2f, 0.2f)) ; // * glm::translate(model_matrix2, glm::vec3(0.0f, 0.0f, -6.0f))    ceci deplace le pion d'une case vers la gauche
                shader.set_uniform_matrix_4fv("model", model_matrix2); //c'est la matrice model qui fait le deplacement scale et rotate
            
                modelPion.render(shader);

                // pion 2
                shader.use();
                glm::mat4 model_matrix3 = glm::mat4(1.0f);
                model_matrix3 = glm::scale(model_matrix3, glm::vec3(0.2f, 0.2f, 0.2f)) * glm::translate(model_matrix3, glm::vec3(0.0f, 0.0f, -6.0f)) ; // * glm::translate(model_matrix2, glm::vec3(0.0f, 0.0f, -6.0f))    ceci deplace le pion d'une case vers la gauche
                shader.set_uniform_matrix_4fv("model", model_matrix3);

                modelPion.render(shader);

                // pion 3
                shader.use();
                glm::mat4 model_matrix4 = glm::mat4(1.0f);
                model_matrix4 = glm::scale(model_matrix4, glm::vec3(0.2f, 0.2f, 0.2f)) * glm::translate(model_matrix4, glm::vec3(0.0f, 0.0f, -12.0f)) ; // * glm::translate(model_matrix2, glm::vec3(0.0f, 0.0f, -6.0f))    ceci deplace le pion d'une case vers la gauche
                shader.set_uniform_matrix_4fv("model", model_matrix4);
                
                modelPion.render(shader);

                // pion 4
                shader.use();
                glm::mat4 model_matrix5 = glm::mat4(1.0f);
                model_matrix5 = glm::scale(model_matrix5, glm::vec3(0.2f, 0.2f, 0.2f)) * glm::translate(model_matrix5, glm::vec3(0.0f, 0.0f, -18.0f)) ; // * glm::translate(model_matrix2, glm::vec3(0.0f, 0.0f, -6.0f))    ceci deplace le pion d'une case vers la gauche
                shader.set_uniform_matrix_4fv("model", model_matrix5);
                                
                modelPion.render(shader);

                // pion 5
                shader.use();
                glm::mat4 model_matrix6 = glm::mat4(1.0f);
                model_matrix6 = glm::scale(model_matrix6, glm::vec3(0.2f, 0.2f, 0.2f)) * glm::translate(model_matrix6, glm::vec3(0.0f, 0.0f, -24.0f)) ; // * glm::translate(model_matrix2, glm::vec3(0.0f, 0.0f, -6.0f))    ceci deplace le pion d'une case vers la gauche
                shader.set_uniform_matrix_4fv("model", model_matrix6);
                                
                modelPion.render(shader);

                // pion 6
                shader.use();
                glm::mat4 model_matrix7 = glm::mat4(1.0f);
                model_matrix7 = glm::scale(model_matrix7, glm::vec3(0.2f, 0.2f, 0.2f)) * glm::translate(model_matrix7, glm::vec3(0.0f, 0.0f, -30.0f)) ; // * glm::translate(model_matrix2, glm::vec3(0.0f, 0.0f, -6.0f))    ceci deplace le pion d'une case vers la gauche
                shader.set_uniform_matrix_4fv("model", model_matrix7);
                                
                modelPion.render(shader);

                // pion 7
                shader.use();
                glm::mat4 model_matrix8 = glm::mat4(1.0f);
                model_matrix8 = glm::scale(model_matrix8, glm::vec3(0.2f, 0.2f, 0.2f)) * glm::translate(model_matrix8, glm::vec3(0.0f, 0.0f, -36.0f)) ; // * glm::translate(model_matrix2, glm::vec3(0.0f, 0.0f, -6.0f))    ceci deplace le pion d'une case vers la gauche
                shader.set_uniform_matrix_4fv("model", model_matrix8);
                                
                modelPion.render(shader);

                // pion 8
                shader.use();
                glm::mat4 model_matrix9 = glm::mat4(1.0f);
                model_matrix9 = glm::scale(model_matrix9, glm::vec3(0.2f, 0.2f, 0.2f)) * glm::translate(model_matrix9, glm::vec3(0.0f, 0.0f, -42.0f)) ; // * glm::translate(model_matrix2, glm::vec3(0.0f, 0.0f, -6.0f))    ceci deplace le pion d'une case vers la gauche
                shader.set_uniform_matrix_4fv("model", model_matrix9);
                                
                modelPion.render(shader);

                //PIONS NOIRS
                shader.use();
                shader.set_uniform_matrix_4fv("model", model_matrix2);                            // c'est la matrice model qui fait le deplacement scale et rotate

                modelPion2.render(shader);

                // pion 2
                shader.use();
                shader.set_uniform_matrix_4fv("model", model_matrix3);

                modelPion2.render(shader);

                // pion 3
                shader.use();
                shader.set_uniform_matrix_4fv("model", model_matrix4);

                modelPion2.render(shader);

                // pion 4
                shader.use();
                shader.set_uniform_matrix_4fv("model", model_matrix5);

                modelPion2.render(shader);

                // pion 5
                shader.use();
                shader.set_uniform_matrix_4fv("model", model_matrix6);

                modelPion2.render(shader);

                // pion 6
                shader.use();
                shader.set_uniform_matrix_4fv("model", model_matrix7);

                modelPion2.render(shader);

                // pion 7
                shader.use();
                shader.set_uniform_matrix_4fv("model", model_matrix8);

                modelPion2.render(shader);

                // pion 8
                shader.use();
                shader.set_uniform_matrix_4fv("model", model_matrix9);

                modelPion2.render(shader);
            
                ImGui::ShowDemoWindow();
            
                ImGui::Begin("Plateau");
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            
                board.drawBoard();
                board.checkGameOver();
            
                ImGui::PopStyleVar();
                ImGui::End(); },
            .key_callback             = [&](int key, int scancode, int action, int mods) { std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << '\n'; },
            .mouse_button_callback    = [&](int button, int action, int mods) { std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << '\n'; },
            .cursor_position_callback = [&](double xpos, double ypos) { camera.track_ball_move_callback(xpos, ypos); },
            .scroll_callback          = [&](double xoffset, double yoffset) { camera.process_scroll(yoffset); },
            .window_size_callback     = [&](int width, int height) { std::cout << "Resized: " << width << ' ' << height << '\n'; },
        }
    );
}
