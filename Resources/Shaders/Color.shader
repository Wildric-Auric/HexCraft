//vertex shader
#version 330 core

layout (location = 0) in vec3 attribPos;
layout (location = 1) in vec2 texCoord;

uniform mat4 uMVP        = mat4(1.0);
//uniform vec3 uModel     = vec3(0.0);

out vec2  uv;
out float grayScale;
void main() {
    mat4 model      = mat4(1.0);
   //model[3]        = vec4(uModel, 1.0);
    vec4 localPos   = vec4(attribPos, 1.0);
    gl_Position     = uMVP * localPos;
    uv              = texCoord;
    grayScale       = gl_Position[2];
}

//fragment shader
#version 330 core

in vec2 uv;
in float grayScale;
out vec4 FragColor;

void main(){
    vec4 col  = vec4(vec3(-grayScale+1.5), 0.0);
    FragColor = col;
}





