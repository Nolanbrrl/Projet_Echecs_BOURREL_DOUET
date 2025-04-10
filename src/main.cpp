#pragma once
#include <imgui.h>
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>
#include <numbers> // For std::numbers::pi
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

    // Variables pour la lumière mobile
    float mobileLight_angle  = 0.0f;
    float mobileLight_height = 3.0f;
    float mobileLight_radius = 7.0f;
    float mobileLight_speed  = 0.5f;

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

                // Mise à jour de la position de la lumière mobile
                if (mobileLight_angle > 2.0f * std::numbers::pi) mobileLight_angle -= 2.0f * std::numbers::pi;
                
                // Calculer la position de la lumière mobile qui tourne autour du plateau
                float x = mobileLight_radius * cos(mobileLight_angle);
                float z = mobileLight_radius * sin(mobileLight_angle);
                glm::vec3 mobileLight_pos = glm::vec3(x, mobileLight_height, z);

                glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                    static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);

                shader.use();
                shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
                shader.set_uniform_matrix_4fv("projection", projection);
                
                if (board.tour_actuel == Color::blanc) {
                    // Lumière fixe pour le tour des blancs: lumière chaude venant d'en haut à droite
                    shader.set_uniform_3fv("lightPos1", glm::vec3(5.0f, 5.0f, 5.0f));
                    shader.set_uniform_3fv("lightColor1", glm::vec3(1.0f, 0.9f, 0.7f)); // Teinte dorée chaude
                    
                    // Lumière mobile secondaire (bleutée plus douce)
                    shader.set_uniform_3fv("lightPos2", mobileLight_pos);
                    shader.set_uniform_3fv("lightColor2", glm::vec3(0.6f, 0.6f, 1.0f));
                    
                    shader.set_uniform_1f("ambientFactor", 0.2f); // Ambiance plus lumineuse
                } 
                else {
                    // Lumière fixe pour le tour des noirs: lumière froide venant d'en bas à gauche
                    shader.set_uniform_3fv("lightPos1", glm::vec3(-5.0f, 3.0f, -3.0f));
                    shader.set_uniform_3fv("lightColor1", glm::vec3(0.7f, 0.8f, 1.0f)); // Teinte bleue froide
                    
                    // Lumière mobile secondaire (ambrée plus douce)
                    shader.set_uniform_3fv("lightPos2", mobileLight_pos);
                    shader.set_uniform_3fv("lightColor2", glm::vec3(0.8f, 0.5f, 0.2f));
                    
                    shader.set_uniform_1f("ambientFactor", 0.15f); // Ambiance plus sombre
                }
                
                shader.set_uniform_3fv("viewPos", camera.get_position());

                board.render3D(shader);
                board.render_pieces3D(shader);

                // Interface ImGui pour contrôler la lumière mobile
                ImGui::ShowDemoWindow();
                ImGui::Begin("Contrôle d'éclairage");
                ImGui::SliderFloat("Vitesse de rotation", &mobileLight_speed, 0.1f, 2.0f, "%.1f");
                ImGui::SliderFloat("Hauteur de la lumière", &mobileLight_height, 0.5f, 10.0f, "%.1f");
                ImGui::SliderFloat("Rayon de rotation", &mobileLight_radius, 3.0f, 15.0f, "%.1f");
                ImGui::End();
                
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