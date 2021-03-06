#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "tools.h"

using namespace glm;

class Camera {
private:
    vec3 _cameraPosition;
    vec3 _initPosition;
    int _xBefore;
    int _yBefore;
    int _wheelBefore;
    float _heading;
    float _pitch;

    inline void initVars() {
        _xBefore = 0;
        _yBefore = 0;
        _wheelBefore = 0;
        _heading = 0;
        _pitch = 0;
        _initPosition = _cameraPosition;
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
        view = view * rotate(mat4(1.0f), -_heading, vec3(1, 0, 0));
        view = view * rotate(mat4(1.0f), -_pitch, vec3(0, 1, 0));
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
        _pitch += deg / 5.0f;
    }

    inline void rotateY(int deg) {
        if (deg == 0)
            return;
         _heading += deg / 5.0f;
    }
    
    inline vec3 viewerPos() const {
//        return _initPosition;
        vec4 res = vec4(_initPosition, 1);
        res = rotate(mat4(1.0f), -_heading, vec3(1, 0, 0)) * res;
        res = rotate(mat4(1.0f), -_pitch, vec3(0, 1, 0)) * res;
        
//        cout << res.x << " " << res.y << " " << res.z << endl;
        return vec3(res.x, res.y, res.z);
    }

    void windowsIterate();

};