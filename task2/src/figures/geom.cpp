
#include "figures/geom.h"
#include <vector>

using namespace std;
using namespace glm;

void fillPlane(std::vector<glm::vec3>& vertices) {

    vertices.push_back(vec3(-1, -1, 0));
    vertices.push_back(vec3(1, 1, 0));
    vertices.push_back(vec3(-1, 1, 0));

    vertices.push_back(vec3(-1, -1, 0));
    vertices.push_back(vec3(1, -1, 0));
    vertices.push_back(vec3(1, 1, 0));

}

void fillCube(std::vector<glm::vec3>& vertices) {

    vertices.push_back(vec3(-1, -1, 1));
    vertices.push_back(vec3(1, 1, 1));
    vertices.push_back(vec3(-1, 1, 1));

    vertices.push_back(vec3(-1, -1, 1));
    vertices.push_back(vec3(1, -1, 1));
    vertices.push_back(vec3(1, 1, 1));
    
    
    
    vertices.push_back(vec3(-1, -1, -1));
    vertices.push_back(vec3(1, 1, -1));
    vertices.push_back(vec3(-1, 1, -1));

    vertices.push_back(vec3(-1, -1, -1));
    vertices.push_back(vec3(1, -1, -1));
    vertices.push_back(vec3(1, 1, -1));
    
}

