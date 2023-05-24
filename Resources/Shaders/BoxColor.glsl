//vertex shader
#version 330 core

layout (location = 0) in vec3  attribPos;
layout (location = 1) in vec2  texCoord;
layout (location = 2) in vec3  upVector;
layout (location = 3) in float texIndex;

uniform mat4 uVP            = mat4(1.0);
uniform mat4 uModel         = mat4(1.0);

out vec2  uv;
out vec3  position;
flat out  vec3  f_up;
flat out  vec3  f_originPosition;
flat out  float f_texInd;

flat out  vec3  f_origin;


out vec3 worldPosition;

void main() {
    mat4 model       = mat4(1.0);
    vec4 localPos    = vec4(attribPos, 1.0);
    gl_Position      = uVP * uModel * localPos;
    uv               = texCoord;

    position         = vec3(vec4(attribPos, 1.0));

    worldPosition    = vec3(uModel * vec4(attribPos, 1.0));
    f_origin         = vec3( vec4(0.0, 0.0, 0.0, 1.0));

    f_up             = vec3(vec4(upVector, 1.0)) ;
    f_originPosition = position;
    f_texInd         = texIndex;
}

//fragment shader
#version 330 core

uniform vec3      uCamPosition  = vec3(1.0);
uniform vec3      uLightSource  = vec3(0.0, 1000.0, -10000.0);
uniform sampler2D uTex0;
uniform float uSpecularStrength = 0.0;
uniform float uSpecularPower    = 256;


in vec2 uv;
in vec3 position;
in vec3 worldPosition;

flat in vec3  f_origin;
flat in vec3  f_up;
flat in vec3  f_originPosition;
flat in float f_texInd;
out vec4 FragColor;

vec3  lightColor        = vec3(1.0, 1.0, 1.0);
vec3  ambientLight      = vec3(0.1);


void main() {
    vec3 fragColor = vec3(1.0);
    vec3 normal;

    vec2 newUV   = uv;
    if (f_texInd == 0.0f) {
        newUV = vec2(uv.x * 0.5, uv.y);
    }

    else if (f_texInd == 1.0f) {
       newUV = uv * 0.5 + 0.5;
    }

    else {
       newUV = vec2(uv.x*0.5 + 0.5, uv.y * 0.5);
    }

    fragColor    = texture2D(uTex0, newUV).xyz;
    if (f_texInd < 1.0) {
        normal       =   cross(f_up, position - f_originPosition);
       float sign    =   dot(normal, f_originPosition - f_origin);

       if (sign < 0.0)
          normal   = cross(position - f_originPosition, f_up);
    }

    else {
            normal   = f_up;
    }

    normal        = normalize(normal);
    vec3 lightDir = normalize(uLightSource - worldPosition);
    vec3 diffuse  = max(dot(normal, lightDir), 0.0) * lightColor;


    vec3 viewDir       = normalize(uCamPosition -  worldPosition);
    vec3 reflectDir    = reflect(-lightDir, normal);

    float spec     = pow(max(dot(viewDir, reflectDir), 0.0), uSpecularPower);
    vec3 specular  = spec * uSpecularStrength * lightColor; 

    vec3 color   = (ambientLight + diffuse + specular) * fragColor;
    
    FragColor = vec4(color, 1.0);
}





