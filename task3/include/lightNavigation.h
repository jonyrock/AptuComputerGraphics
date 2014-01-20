#pragma once

#include <GL/glfw.h>
#include <GL/glew.h>

#include <iostream>



using namespace std;

class LightNavigation {
    GLuint _programId;
    
    GLuint _is_blinnId;
    GLuint _ambientId;
    GLuint _diffuseId;
    GLuint _specularId;
    GLuint _specular_powerId;    
    GLuint _kcId;
    GLuint _klId;
    GLuint _kqId;
    
    int _is_blinn;
    float _ambient;
    float _diffuse;
    float _specular;
    float _specular_power;
    float _kc;
    float _kl;
    float _kq;

public:

    LightNavigation(GLuint programId)
    : _programId(programId) {
        
        _is_blinn = false;
        
        _ambient = 0.3f;
        _diffuse = 0.5f;
        _specular = 1.0f;
        _specular_power = 1.98f;
        
        _kc = 1.0f;
        _kl = 0.000001f;
        _kq = 0.0000000001f;
        
        _is_blinnId = glGetUniformLocation(programId, "is_blinn");
        
        _ambientId = glGetUniformLocation(programId, "ambient");
        _diffuseId = glGetUniformLocation(programId, "diffuse");
        _specularId = glGetUniformLocation(programId, "specular");
        _specular_powerId = glGetUniformLocation(programId, "specular_power");
        
        
        _kcId = glGetUniformLocation(programId, "kc");
        _klId = glGetUniformLocation(programId, "kl");
        _kqId = glGetUniformLocation(programId, "kq");
        

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
        
        if (glfwGetKey('F') == GLFW_PRESS)
            _kc -= 0.01;
        if (glfwGetKey('G') == GLFW_PRESS)
            _kc += 0.01;
        
        if (glfwGetKey('H') == GLFW_PRESS)
            _kl -= 0.000001f;
        if (glfwGetKey('J') == GLFW_PRESS)
            _kl += 0.000001f;
        
        if (glfwGetKey('K') == GLFW_PRESS)
            _kq -= 0.0000000001f;
        if (glfwGetKey('L') == GLFW_PRESS)
            _kq += 0.0000000001f;

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
        
        glUniform1i(_is_blinnId, _is_blinn);
        glUniform1f(_ambientId, _ambient);
        glUniform1f(_diffuseId, _diffuse);
        glUniform1f(_specularId, _specular);
        glUniform1f(_specular_powerId, _specular_power);
        
        glUniform1f(_kcId, _kc);
        glUniform1f(_klId, _kl);
        glUniform1f(_kqId, _kq);
        
    }

    inline void draw() {

    }



};