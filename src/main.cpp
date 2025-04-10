#pragma once
#include <imgui.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Board.hpp"
#include "Camera.hpp"
#include "Model3D.hpp"
#include "Shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "quick_imgui/quick_imgui.hpp"

bool isCKeyPressed = false;

void renderModel(glmax::Shader& shader, Model3D& model, const glm::mat4& transform)
{
    shader.use();
    shader.set_uniform_matrix_4fv("model", transform);
    model.render(shader);
}

void handleKeyEvent(int key, bool isPressed)
{
    if (key == 'C' || key == 'c')
    {
        isCKeyPressed = isPressed;
    }
}

int main()
{
    int           window_width  = 1280;
    int           window_height = 720;
    glmax::Shader shader;
    glmax::Camera camera{true};
    Board         board;

    quick_imgui::loop(
        "Quick ImGui",
        {
            .init                     = [&]() {
                std::cout << "Init\n";
                shader.load_shader("model.vs.glsl", "model.fs.glsl");
            
                // Initialiser le plateau et ses pièces
                board.initializeBoard3D("board/board.obj", "board"); },
            .loop                     = [&]() {
                glClearColor(0.847f, 0.82f, 0.929f, 1.f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);

                glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                    static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);

                shader.use();
                shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
                shader.set_uniform_matrix_4fv("projection", projection);
                shader.set_uniform_3fv("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
                shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
                shader.set_uniform_3fv("viewPos", camera.get_position());


                board.render3D(shader);
                board.render_pieces3D(shader);

                ImGui::ShowDemoWindow();
                ImGui::Begin("Plateau");
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
                board.drawBoard();
                board.checkGameOver();
                ImGui::PopStyleVar();
                ImGui::End(); },
            .key_callback             = [&](int key, int scancode, int action, int mods) {
                    bool isPressed = (action != 0); 
                    handleKeyEvent(key, isPressed);
                    std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << '\n'; },
            .cursor_position_callback = [&](double xpos, double ypos) {
                    if (isCKeyPressed) { 
                        camera.track_ball_move_callback(xpos, ypos);
                    } },
            .scroll_callback          = [&](double xoffset, double yoffset) {
                    if (isCKeyPressed) { 
                        camera.process_scroll(yoffset);
                    } },
            .window_size_callback     = [&](int width, int height) { std::cout << "Resized: " << width << ' ' << height << '\n'; },
        }
    );
}