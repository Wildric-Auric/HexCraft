//vertex shader
#version 330 core

layout (location = 0) in vec3  attribPos;
layout (location = 1) in vec2  texCoord;
layout (location = 2) in vec3  upVector;
layout (location = 3) in float texIndex;

uniform mat4 uVP            = mat4(1.0);

out vec2  uv;
flat out  float f_texInd;
flat out  float f_texBatchInd;
flat out  vec3  f_originPosition;
flat out  vec3  f_origin;

out vec3 worldPosition;

void main() {
    mat4 model       = mat4(1.0);
    vec4 localPos    = vec4(attribPos, 1.0);
    gl_Position      = uVP * localPos;
    uv               = texCoord;

    worldPosition    = attribPos;

    f_originPosition = worldPosition;
    f_origin         = upVector;

    f_texBatchInd    = float(int(texIndex / 100.0));
    f_texInd         = mod(texIndex, 100.0);
}

//fragment shader
#version 330 core

uniform vec3      uCamPosition      = vec3(1.0);
uniform vec3      uLightSource      = vec3(0.0, 1000.0, -10000.0);
uniform sampler2D uTex[32];
uniform float     uSpecularStrength = 0.0;
uniform float     uSpecularPower    = 256;


in vec2 uv;
in vec3 worldPosition;  

flat in float f_texInd;
flat in float f_texBatchInd;
flat in vec3  f_originPosition;
flat in vec3  f_origin;

out vec4 FragColor;

vec3  lightColor        = vec3(1.0);
vec3  ambientLight      = vec3(0.25); 

void main() {
    vec3 fragColor = vec3(1.0);
    vec3 normal;

    vec2 newUV   = uv;
    if (f_texInd  <= 0.001f) {
        newUV = vec2(uv.x * 0.5, uv.y);
    }

    else if (f_texInd <= 1.001 && f_texInd >= 0.99) {
       newUV = uv * 0.5 + 0.5;
    }

    else {
       newUV = vec2(uv.x*0.5 + 0.5, uv.y * 0.5);
    }

    fragColor    = texture2D(uTex[int(f_texBatchInd) - 1], newUV).xyz;
    if (f_texInd < 1.0) {
        normal       =   cross(vec3(0.0, 1.0, 0.0), worldPosition - f_originPosition);
        float sign   =   dot(normal, f_originPosition - f_origin);

        if (sign <= 0.0)
            normal     = cross(worldPosition - f_originPosition, vec3(0.0, 1.0, 0.0));
    }

    else if (f_texInd == 1.0) {
            normal     = vec3(0.0, 1.0, 0.0);
    }

    else if (f_texInd == 2.0) {
            normal     = vec3(0.0, -1.0, 0.0);
    }   

    normal        = normalize(normal);
    vec3 lightDir = normalize(uLightSource - worldPosition);
    vec3 diffuse  = max(dot(normal, lightDir), 0.0) * lightColor;


    vec3 viewDir       = normalize(uCamPosition -  worldPosition);
    vec3 reflectDir    = reflect(-lightDir, normal);

    float spec     = pow(max(dot(viewDir, reflectDir), 0.0), uSpecularPower);
    vec3 specular  = spec * uSpecularStrength * lightColor; 

    vec3 color   = (/*ambientLight+*/ diffuse + specular) * fragColor;
    FragColor = vec4(color, 1.0);
}





