#pragma once

#include <GL/glfw.h>
#include <GL/glew.h>

class TextureNavigation {
    GLuint _textureID;
    GLuint _textureScaleId;
    float _ts;

public:

    TextureNavigation(GLuint textureID, GLuint textureScaleId)
    : _textureID(textureID), _textureScaleId(textureScaleId) {
        _ts = 1;
    }

    inline void windowsIterate() {
        if (glfwGetKey(GLFW_KEY_KP_ADD) == GLFW_PRESS)
            _ts -= 0.1;
        if (glfwGetKey(GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
            _ts += 0.1;

        glUniform1f(_textureScaleId, _ts);
        setTexturesParam();
    }

private:

    inline void setTexturesParam() {

        glBindTexture(GL_TEXTURE_2D, _textureID);

        // Poor filtering, or ...
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //    glGenerateMipmap(GL_TEXTURE_2D);

    }



};