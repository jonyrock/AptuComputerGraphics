#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;


// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 M; // always id
uniform vec3 vertexColor;
uniform vec3 viewerPos;


out vec3 fragmentColor;
out vec3 fragmentNormal;
out vec3 fragmentPos;
out vec3 fviewerPos;

void main() {
    gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
    fragmentPos = vertexPosition_modelspace;
    fragmentColor = vertexColor;
    fragmentNormal = normalize(vertexNormal_modelspace);
    fviewerPos = normalize(viewerPos);
}

