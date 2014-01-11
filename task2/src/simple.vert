#version 120

// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition_modelspace;
uniform vec3 vertexColor;
uniform float isWireframe;
uniform float nearClippingPlaneId;
uniform float farClippingPlaneId;

// Output data ; will be interpolated for each fragment.
varying vec3 fragmentColor;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main() {
    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
    // The color of each vertex will be interpolated
    // to produce the color of each fragment
    float bright = (-gl_Position.z - nearClippingPlaneId) / 
                   (farClippingPlaneId - nearClippingPlaneId);
    
    bright += 0.15;
    bright *= 10;
    if(isWireframe == 1.0)
        fragmentColor = vec3(1.0, 1.0, 1.0);
    else
        fragmentColor = vec3(.7f, .5f, .5f);
    
    // it is not used, see simple.frag
    // fragmentColor *= bright;

}