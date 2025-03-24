#version 330 core

layout(location = 0) in vec3 aPos; // Vertex position
layout(location = 1) in vec3 aColor; // Vertex color

out vec3 vertexColor; // Output color to fragment shader

uniform mat4 model; // Model transformation matrix
uniform mat4 view; // View transformation matrix
uniform mat4 projection; // Projection transformation matrix

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0); // Transform vertex position
    vertexColor = aColor; // Pass color to fragment shader
}