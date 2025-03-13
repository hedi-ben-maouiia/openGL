#version 330 core 

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;  // Texture coordinates

out vec2 TexCoord;  // Pass the texture coordinates to the fragment shader

void main() {
    gl_Position = vec4(aPos, 1.0);
    TexCoord = aTexCoord;  // Set the texture coordinates
}
