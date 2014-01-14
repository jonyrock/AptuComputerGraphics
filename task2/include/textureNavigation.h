#pragma once

#include <GL/glfw.h>
#include <GL/glew.h>

#include <iostream>
using namespace std;

class TextureNavigation {
    GLuint _textureID;
    GLuint _textureScaleId;
    float _ts;
    int _filterType;

public:

    TextureNavigation(GLuint textureID_, GLuint textureScaleId_)
    : _textureID(textureID_), _textureScaleId(textureScaleId_) {
        _ts = 1;
        _filterType = 1;
    }

    inline void windowsIterate() {
        if (glfwGetKey(GLFW_KEY_KP_ADD) == GLFW_PRESS)
            _ts -= 0.1;
        if (glfwGetKey(GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
            _ts += 0.1;
        glUniform1f(_textureScaleId, _ts);

        for (int i = 1; i <= 6; i++) {
            if (glfwGetKey('0' + i) == GLFW_PRESS)
                _filterType = i;
        }

        setTexturesParam();
    }
    
    inline void textureId(GLuint textureID_) {
        _textureID = textureID_;
    }
    
private:

    inline void setTexturesParam() {

        glBindTexture(GL_TEXTURE_2D, _textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        if (_filterType == 1) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        }

        if (_filterType == 2) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }

        if (_filterType == 3) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        }
        
        if (_filterType == 4) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        }
        
        if (_filterType == 5) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        }
        
        if (_filterType == 6) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        }


        if (_filterType > 2) {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

    }



};