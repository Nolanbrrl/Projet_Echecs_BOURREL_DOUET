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

    Model3D whitePawnModel, blackPawnModel, boardModel, whiteRookModel, blackRookModel;
    Model3D whiteKnightModel, blackKnightModel, whiteBishopModel, blackBishopModel;
    Model3D whiteKingModel, blackKingModel, whiteQueenModel, blackQueenModel;

    quick_imgui::loop(
        "Quick ImGui",
        {
            .init                     = [&]() {
                std::cout << "Init\n";
                shader.load_shader("model.vs.glsl", "model.fs.glsl");
            
                // Load and setup models
                whitePawnModel.load_mesh("pawn/pawn.obj", "pawn");
                blackPawnModel.load_mesh("pawn/pawn2.obj", "pawn");
                whiteRookModel.load_mesh("rook/tower.obj", "rook");
                blackRookModel.load_mesh("rook/tower2.obj", "rook");
                whiteKnightModel.load_mesh("knight/cavalier.obj", "knight");
                blackKnightModel.load_mesh("knight/cavalier2.obj", "knight");
                whiteBishopModel.load_mesh("bishop/fou.obj", "bishop");
                blackBishopModel.load_mesh("bishop/fou2.obj", "bishop");
                boardModel.load_mesh("board/board.obj", "board");
                whiteKingModel.load_mesh("king/king.obj", "king");
                blackKingModel.load_mesh("king/king2.obj", "king");
                whiteQueenModel.load_mesh("queen/queen.obj", "queen");
                blackQueenModel.load_mesh("queen/queen2.obj", "queen");
            
                whitePawnModel.setup_buffers();
                blackPawnModel.setup_buffers();
                whiteRookModel.setup_buffers();
                blackRookModel.setup_buffers();
                whiteKnightModel.setup_buffers();
                blackKnightModel.setup_buffers();
                whiteBishopModel.setup_buffers();
                blackBishopModel.setup_buffers();
                whiteKingModel.setup_buffers();
                blackKingModel.setup_buffers();
                whiteQueenModel.setup_buffers();
                blackQueenModel.setup_buffers();
                boardModel.setup_buffers(); },
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
                glm::mat4 basePosition = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f));
                renderModel(shader, boardModel, basePosition);

                // Render white pawns
                for (int i = 0; i < 8; ++i) {
                    glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f * i));
                    renderModel(shader, whitePawnModel, transform);
                }

                // Render black pawns
                for (int i = 0; i < 8; ++i) {
                    glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f * i));
                    renderModel(shader, blackPawnModel, transform);
                }

                renderModel(shader, whiteRookModel, basePosition);
                renderModel(shader, whiteRookModel, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                                    glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -42.0f))); 
                renderModel(shader, blackRookModel, basePosition);
                renderModel(shader, blackRookModel, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                                    glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -42.0f))); 
                renderModel(shader, whiteKnightModel, basePosition);
                renderModel(shader, whiteKnightModel, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                                    glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -30.0f)));
                renderModel(shader, blackKnightModel, basePosition);
                renderModel(shader, blackKnightModel, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                                    glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -30.0f))); 
                renderModel(shader, whiteBishopModel, basePosition);
                renderModel(shader, whiteBishopModel, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                                    glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -18.0f))); 
                renderModel(shader, blackBishopModel, basePosition);
                renderModel(shader, blackBishopModel, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                                    glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -18.0f))); 
                renderModel(shader, whiteQueenModel, basePosition);
                renderModel(shader, blackQueenModel, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                                    glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 6.0f))); 
                renderModel(shader, whiteKingModel, basePosition);
                renderModel(shader, blackKingModel, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)) *
                                                    glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f)));
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