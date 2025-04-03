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

// Utility function to render a model with a specific transformation matrix
void renderModel(glmax::Shader& shader, Model3D& model, const glm::mat4& transform)
{
    shader.use();
    shader.set_uniform_matrix_4fv("model", transform);
    model.render(shader);
}

int main()
{
    int           window_width  = 1280;
    int           window_height = 720;
    glmax::Shader shader;
    glmax::Camera camera{true};
    Board         board;

    Model3D modelPion, modelPion2, modelPlateau, modelTour, modelTour2;
    Model3D modelCavalier, modelCavalier2, modelFou, modelFou2;
    Model3D modelRoi, modelRoi2, modelReine, modelReine2;

    quick_imgui::loop(
        "Quick ImGui",
        {
            .init                     = [&]() {
                std::cout << "Init\n";
                shader.load_shader("model.vs.glsl", "model.fs.glsl");

                // Load and setup models
                modelPion.load_mesh("pawn/pawn.obj", "pawn");
                modelPion2.load_mesh("pawn/pawn2.obj", "pawn");
                modelTour.load_mesh("rook/tower.obj", "rook");
                modelTour2.load_mesh("rook/tower2.obj", "rook");
                modelCavalier.load_mesh("knight/cavalier.obj", "knight");
                modelCavalier2.load_mesh("knight/cavalier2.obj", "knight");
                modelFou.load_mesh("bishop/fou.obj", "bishop");
                modelFou2.load_mesh("bishop/fou2.obj", "bishop");
                modelPlateau.load_mesh("board/board.obj", "board");
                modelRoi.load_mesh("king/king.obj", "king");
                modelRoi2.load_mesh("king/king2.obj", "king");
                modelReine.load_mesh("queen/queen.obj", "queen");
                modelReine2.load_mesh("queen/queen2.obj", "queen");

                modelPion.setup_buffers();
                modelPion2.setup_buffers();
                modelTour.setup_buffers();
                modelTour2.setup_buffers();
                modelCavalier.setup_buffers();
                modelCavalier2.setup_buffers();
                modelFou.setup_buffers();
                modelFou2.setup_buffers();
                modelRoi.setup_buffers();
                modelRoi2.setup_buffers();
                modelReine.setup_buffers();
                modelReine2.setup_buffers();
                modelPlateau.setup_buffers(); },
            .loop                     = [&]() {
                glClearColor(0.847f, 0.82f, 0.929f, 1.f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);

                glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);

                // Set common shader uniforms
                shader.use();
                shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
                shader.set_uniform_matrix_4fv("projection", projection);
                shader.set_uniform_3fv("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
                shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
                shader.set_uniform_3fv("viewPos", camera.get_position());

                // Render the board
                glm::mat4 positionDeBase = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f));
                renderModel(shader, modelPlateau, positionDeBase);

                // Render white pawns
                for (int i = 0; i < 8; ++i) {
                    glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                          glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f * i));
                    renderModel(shader, modelPion, transform);
                }

                // Render black pawns
                for (int i = 0; i < 8; ++i) {
                    glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                          glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f * i));
                    renderModel(shader, modelPion2, transform);
                }

                renderModel(shader, modelTour, positionDeBase); // White rook
                renderModel(shader, modelTour, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                                glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -42.0f))); // White rook
                renderModel(shader, modelTour2, positionDeBase); // Black rook
                renderModel(shader, modelTour2, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -42.0f))); // Black rook
                renderModel(shader, modelCavalier, positionDeBase); // White knight
                renderModel(shader, modelCavalier, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                                glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -30.0f))); // White knight
                renderModel(shader, modelCavalier2, positionDeBase); // Black knight
                renderModel(shader, modelCavalier2, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -30.0f))); // Black knight
                renderModel(shader, modelFou, positionDeBase); // White bishop
                renderModel(shader, modelFou, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                                glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -18.0f))); // White bishop
                renderModel(shader, modelFou2, positionDeBase); // Black bishop
                renderModel(shader, modelFou2, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -18.0f))); // Black bishop
                renderModel(shader, modelReine, positionDeBase); // White queen
                renderModel(shader, modelReine2, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                                glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 6.0f))); // Black queen
                renderModel(shader, modelRoi, positionDeBase); // White king
                renderModel(shader, modelRoi2, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                                glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f))); // Black king

                // ImGui interface
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