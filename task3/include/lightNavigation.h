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
    GLuint _is_blinnId;

    float _ambient;
    float _diffuse;
    float _specular;
    float _specular_power;
    int _is_blinn;

public:

    LightNavigation(GLuint programId)
    : _programId(programId) {
        _ambient = 0.3f;
        _diffuse = 0.5f;
        _specular = 0.8f;
        _specular_power = 1.98f;
        _is_blinn = false;

        _ambientId = glGetUniformLocation(programId, "ambient");
        _diffuseId = glGetUniformLocation(programId, "diffuse");
        _specularId = glGetUniformLocation(programId, "specular");
        _specular_powerId = glGetUniformLocation(programId, "specular_power");
        _is_blinnId = glGetUniformLocation(programId, "is_blin");
        

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
        
        if (glfwGetKey('1') == GLFW_PRESS)
            _is_blinn = 0;
        
        if (glfwGetKey('2') == GLFW_PRESS)
            _is_blinn = 1;

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

        glUniform1f(_ambientId, _ambient);
        glUniform1f(_diffuseId, _diffuse);
        glUniform1f(_specularId, _specular);
        glUniform1f(_specular_powerId, _specular_power);
        glUniform1i(_is_blinnId, _is_blinn);

    }

    inline void draw() {

    }



};