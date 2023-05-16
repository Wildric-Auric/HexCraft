//vertex shader
#version 330 core

layout (location = 0) in vec3 attribPos;
layout (location = 1) in vec2 texCoord;

out vec2 uv;

void main() {
    gl_Position = vec4(attribPos, 1.0);
    uv = texCoord;
};

//fragment shader
#version 330 core

in vec2 uv;
out vec4 FragColor;

void main(){
    vec4 col = vec4(1.0);
    FragColor = col;
}





