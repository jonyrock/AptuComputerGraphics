
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

    for (int i = 0; i <= 6; i++) {
        vertices.push_back(vec2(1, 0));
        vertices.push_back(vec2(0, 1));
        vertices.push_back(vec2(0, 0));

        vertices.push_back(vec2(1, 0));
        vertices.push_back(vec2(1, 1));
        vertices.push_back(vec2(0, 1));
    }

}

