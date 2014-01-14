
#include "figures/textures.h"

#include <iostream>

using namespace std;
using namespace glm;



void fillPlaneUV(std::vector<glm::vec2>& vertices) {

    vertices = {
        vec2(1, 0),
        vec2(0, 1),
        vec2(0, 0),

        vec2(1, 0),
        vec2(1, 1),
        vec2(0, 1)
    };

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

void fillSphereUV(std::vector<glm::vec2>& vertices) {

    //    cout << "fill sphere" << endl;

    float step = 2;

    for (float beta = 0; beta < 360; beta += step) {
        for (float alpha = 0; alpha < 360; alpha += step) {

            

            /***********
             * b ---- c
             * |      |
             * |      |
             * a ---- d
             * ********/
            
            
            
            float alpha_ = alpha / 360;
            float beta_ = beta / 360;
            float step_ = step / 360;
            
//            cout << "(" << alpha_ << ", " << beta_ << "), ";
//            cout << "(" << alpha_ + step_ << ", " << beta_ << "), ";
//            cout << "(" << alpha_ + step_ << ", " << beta_ + step_ << "), ";
//            cout << "(" << alpha_ << ", " << beta_ + step_ << ") ";
//            cout << endl;

            vec2 a(alpha_, beta_);
            vec2 b(alpha_ + step_, beta_);
            vec2 c(alpha_ + step_, beta_ + step_);
            vec2 d(alpha_, beta_ + step_);

            vertices.push_back(a);
            vertices.push_back(c);
            vertices.push_back(b);

            vertices.push_back(a);
            vertices.push_back(d);
            vertices.push_back(c);
        }

    }
}

