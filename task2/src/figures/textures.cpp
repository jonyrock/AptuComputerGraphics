
#include "figures/textures.h"

using namespace std;
using namespace glm;

void fillPlaneUV(std::vector<glm::vec2>& vertices) {

    vertices.push_back(vec2(1, 0));
    vertices.push_back(vec2(0, 1));
    vertices.push_back(vec2(0, 0));
    
    vertices.push_back(vec2(1, 0));
    vertices.push_back(vec2(1, 1));
    vertices.push_back(vec2(0, 1));

}

void fillCubeUV(std::vector<glm::vec2>& vertices) {
    vertices.push_back(vec2(0.000059f, 1.0f - 0.000004f));
    vertices.push_back(vec2(0.000103f, 1.0f - 0.336048f));
    vertices.push_back(vec2(0.335973f, 1.0f - 0.335903f));
    vertices.push_back(vec2(1.000023f, 1.0f - 0.000013f));
    vertices.push_back(vec2(0.667979f, 1.0f - 0.335851f));
    vertices.push_back(vec2(0.999958f, 1.0f - 0.336064f));
    vertices.push_back(vec2(0.667979f, 1.0f - 0.335851f));
    vertices.push_back(vec2(0.336024f, 1.0f - 0.671877f));
    vertices.push_back(vec2(0.667969f, 1.0f - 0.671889f));
    vertices.push_back(vec2(1.000023f, 1.0f - 0.000013f));
    vertices.push_back(vec2(0.668104f, 1.0f - 0.000013f));
    vertices.push_back(vec2(0.667979f, 1.0f - 0.335851f));
    vertices.push_back(vec2(0.000059f, 1.0f - 0.000004f));
    vertices.push_back(vec2(0.335973f, 1.0f - 0.335903f));
    vertices.push_back(vec2(0.336098f, 1.0f - 0.000071f));
    vertices.push_back(vec2(0.667979f, 1.0f - 0.335851f));
    vertices.push_back(vec2(0.335973f, 1.0f - 0.335903f));
    vertices.push_back(vec2(0.336024f, 1.0f - 0.671877f));
    vertices.push_back(vec2(1.000004f, 1.0f - 0.671847f));
    vertices.push_back(vec2(0.999958f, 1.0f - 0.336064f));
    vertices.push_back(vec2(0.667979f, 1.0f - 0.335851f));
    vertices.push_back(vec2(0.668104f, 1.0f - 0.000013f));
    vertices.push_back(vec2(0.335973f, 1.0f - 0.335903f));
    vertices.push_back(vec2(0.667979f, 1.0f - 0.335851f));
    vertices.push_back(vec2(0.335973f, 1.0f - 0.335903f));
    vertices.push_back(vec2(0.668104f, 1.0f - 0.000013f));
    vertices.push_back(vec2(0.336098f, 1.0f - 0.000071f));
    vertices.push_back(vec2(0.000103f, 1.0f - 0.336048f));
    vertices.push_back(vec2(0.000004f, 1.0f - 0.671870f));
    vertices.push_back(vec2(0.336024f, 1.0f - 0.671877f));
    vertices.push_back(vec2(0.000103f, 1.0f - 0.336048f));
    vertices.push_back(vec2(0.336024f, 1.0f - 0.671877f));
    vertices.push_back(vec2(0.335973f, 1.0f - 0.335903f));
    vertices.push_back(vec2(0.667969f, 1.0f - 0.671889f));
    vertices.push_back(vec2(1.000004f, 1.0f - 0.671847f));
    vertices.push_back(vec2(0.667979f, 1.0f - 0.335851f));
}

