//vertex shader
#version 330 core

layout (location = 0) in vec3 attribPos;
layout (location = 1) in vec2 texCoord;

uniform mat4 uMVP        = mat4(1.0);

out vec2  uv;
out float grayScale;

void main() {
    mat4 model      = mat4(1.0);
    vec4 localPos   = vec4(attribPos, 1.0);
    gl_Position     = uMVP * localPos;
    uv              = texCoord;
}

//fragment shader
#version 330 core

in vec2 uv;
out vec4 FragColor;

void main(){
    vec3 color = vec3(1.0);
    FragColor = vec4(color, 1.0);
}





