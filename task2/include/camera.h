#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Camera {
    
private:
    vec3 _cameraPosition;
    int _xBefore;
    int _yBefore;
    int _wheelBefore;
    
    inline void initVars(){
        _xBefore = 0;
        _yBefore = 0;
        _wheelBefore = 0;
    }
        
public:
    
    
    
    Camera(float x, float y, float z) : _cameraPosition(x, y, z) {
        initVars();
    }
    
    Camera(vec3 cameraPosition) : _cameraPosition(cameraPosition) {
        initVars();
    }
    
    inline void updateView(mat4& view) {
        view = lookAt(_cameraPosition, vec3(0, 0, 0), vec3(0, 1, 0));
    }

    inline void zoom(float scale = 1) {
        if (scale == 0)
            return;
        vec3 uv = glm::normalize(_cameraPosition);
        float magnitude = dot(_cameraPosition, _cameraPosition);
        if (magnitude + scale < 0)
            return;
        uv *= scale;
        _cameraPosition += uv;
    }
    
    inline void rotateX(int deg) {
        if (deg == 0)
            return;
        auto rm = rotate(mat4(), deg / 5.0f, vec3(0.0f, 1.0f, 0.0f));
        auto v4 = rm * glm::vec4(_cameraPosition, 1);
        _cameraPosition[0] = v4[0];
        _cameraPosition[1] = v4[1];
        _cameraPosition[2] = v4[2];
    }

    inline void rotateY(int deg) {
        if (deg == 0)
            return;
        auto rm = rotate(mat4(), deg / 5.0f, vec3(1.0f, 0.0f, 0.0f));
        auto v4 = rm * glm::vec4(_cameraPosition, 1);
        _cameraPosition[0] = v4[0];
        _cameraPosition[1] = v4[1];
        _cameraPosition[2] = v4[2];
    }
    
    void windowsIterate();
    
};