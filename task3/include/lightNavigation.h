#pragma once

#include <GL/glfw.h>
#include <GL/glew.h>

#include <iostream>



using namespace std;

class LightNavigation {
    GLuint _programId;

    GLuint _ambientId;
    GLuint _diffuseId;
    GLuint _specularId;
    GLuint _specular_powerId;

    float _ambient;
    float _diffuse;
    float _specular;
    float _specular_power;

public:

    LightNavigation(GLuint programId)
    : _programId(programId) {
        _ambient = 0.4f;
        _diffuse = 0.4f;
        _specular = 0.3f;
        _specular_power = 0.3f;

        _ambientId = glGetUniformLocation(programId, "ambient");
        _diffuseId = glGetUniformLocation(programId, "diffuse");
        _specularId = glGetUniformLocation(programId, "specular");
        _specular_powerId = glGetUniformLocation(programId, "specular_power");

    }

    inline void windowsIterate() {
        if (glfwGetKey('Z') == GLFW_PRESS)
            _ambient -= 0.05;
        if (glfwGetKey('X') == GLFW_PRESS)
            _ambient += 0.05;

        if (glfwGetKey('C') == GLFW_PRESS)
            _diffuse -= 0.05;
        if (glfwGetKey('V') == GLFW_PRESS)
            _diffuse += 0.05;

        if (glfwGetKey('B') == GLFW_PRESS)
            _specular -= 0.05;
        if (glfwGetKey('N') == GLFW_PRESS)
            _specular += 0.05;

        if (glfwGetKey(',') == GLFW_PRESS)
            _specular_power -= 0.01;
        if (glfwGetKey('.') == GLFW_PRESS)
            _specular_power += 0.01;

        updateParams();
    }

private:

    inline void updateParams() {
        if (_ambient < 0)
            _ambient = 0;
        if (_diffuse < 0)
            _diffuse = 0;
        if (_specular < 0)
            _specular = 0;
        if (_specular_power < 0)
            _specular_power = 0;

        cout << _specular_power  << endl;
        glUniform1f(_ambientId, _ambient);
        glUniform1f(_diffuseId, _diffuse);
        glUniform1f(_specularId, _specular);
        glUniform1f(_specular_powerId, _specular_power);

    }

    inline void draw() {

    }



};