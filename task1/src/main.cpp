#include "shader.hpp"
#include "objloader.hpp"

#include <iostream>
#include <vector>

#include <GL/glfw.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

using namespace std;
using namespace glm;

typedef unsigned char uchar;

mat4 View;
vec3 cameraPosition(6, 0, 10);

void zoom(float scale = 1) {
    if (scale == 0)
        return;
    vec3 uv = glm::normalize(cameraPosition);
    float magnitude = dot(cameraPosition, cameraPosition);
    if (magnitude + scale < 0)
        return;
    uv *= scale;
    cameraPosition += uv;
}

void update_view() {
    View = lookAt(cameraPosition, vec3(0, 0, 0), vec3(0, 1, 0));
}

void rotate_x(int deg) {
    if (deg == 0)
        return;
    auto rm = rotate(mat4(), deg / 5.0f, vec3(0.0f, 1.0f, 0.0f));
    auto v4 = rm * glm::vec4(cameraPosition, 1);
    cameraPosition[0] = v4[0];
    cameraPosition[1] = v4[1];
    cameraPosition[2] = v4[2];
//    cout << "r" << deg << endl;
}

void rotate_y(int deg) {
    if (deg == 0)
        return;
    
//    swap(cameraPosition[0], cameraPosition[1]);
    auto rm = rotate(mat4(), deg / 5.0f, vec3(1.0f, 0.0f, 0.0f));
    auto v4 = rm * glm::vec4(cameraPosition, 1);
    cameraPosition[0] = v4[0];
    cameraPosition[1] = v4[1];
    cameraPosition[2] = v4[2];
//    cout << cameraPosition. << endl;
//    swap(cameraPosition[0], cameraPosition[1]);
//    cout << "r" << deg << endl;
}

int main(void) {

    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

    if (!glfwOpenWindow(700, 600, 0, 0, 0, 0, 32, 0, GLFW_WINDOW)) {
        cerr << "Failed to open GLFW window." << endl;
        glfwTerminate();
        return -1;
    }
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW" << endl;
        return -1;
    }

    glfwSetWindowTitle("Cow party");
    glfwEnable(GLFW_STICKY_KEYS);

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    // MVP init
    float NEAR_CLIPPING_PLANE = 0.1f;
    float FAR_CLIPPING_PLANE = 100.0f;
    mat4 Projection = perspective(45.0f, 4.0f / 3.0f, NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE);

    update_view();
    mat4 Model = mat4(0.f);
    Model[0][0] = 1;
    Model[1][1] = 1;
    Model[2][2] = 1;

    Model[3][0] = -1;
    Model[3][1] = -1;
    Model[3][3] = 1;
    mat4 MVP;

    // GLSL init
    GLuint programId = LoadShaders("src/simple.vert", "src/simple.frag");
    GLuint mvpId = glGetUniformLocation(programId, "MVP");
    GLuint vertexColorId = glGetUniformLocation(programId, "vertexColor");
    GLuint vertexPosition_modelspaceID = glGetAttribLocation(programId, "vertexPosition_modelspace");
    GLuint isWireframeId = glGetUniformLocation(programId, "isWireframe");
    GLuint nearClippingPlaneId = glGetUniformLocation(programId, "nearClippingPlaneId");
    GLuint farClippingPlaneId = glGetUniformLocation(programId, "farClippingPlaneId");
    glUseProgram(programId);

    glUniform1f(nearClippingPlaneId, NEAR_CLIPPING_PLANE);
    glUniform1f(farClippingPlaneId, FAR_CLIPPING_PLANE);

    // Model init
    vector<vec3> vertices;
    vector<vec2> uvs;
    vector<vec3> normals;
    loadOBJ("resources/model.obj", vertices, uvs, normals);

    // GPU buffers initEXECFUNCTION
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof (vec3), &vertices[0], GL_STATIC_DRAW);

    int wheelBefore = glfwGetMouseWheel();
    int xBefore = 0;
    int yBefore = 0;


    glClearColor(0.9f, 0.9f, 0.9f, 0.0f);

    do {

        if (glfwGetKey('W') == GLFW_PRESS) {
            zoom(-0.3);
        }

        if (glfwGetKey('S') == GLFW_PRESS) {
            zoom(0.3);
        }

        int myX = 0;
        int myY = 0;
        glfwGetMousePos(&myX, &myY);
        int xDiff = myX - xBefore;
        int yDiff = myY - yBefore;
        xBefore = myX;
        yBefore = myY;

        if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            rotate_x(-xDiff);
            rotate_y(-yDiff);
        }

        int myWheel = glfwGetMouseWheel();
        int wheelDiff = myWheel - wheelBefore;
        zoom(-wheelDiff);
        wheelBefore = myWheel;

        update_view();

        MVP = Projection * View * Model;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(mvpId, 1, GL_FALSE, &MVP[0][0]);
        glEnableVertexAttribArray(vertexPosition_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(vertexPosition_modelspaceID, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        glUniform1f(isWireframeId, 1.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        glPolygonOffset(1.0f, 1.0f);
        glDisable(GL_POLYGON_OFFSET_FILL);


        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glUniform1f(isWireframeId, 0.0f);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        //        
        glDisableVertexAttribArray(vertexPosition_modelspaceID);
        glfwSwapBuffers();

    } while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
            glfwGetWindowParam(GLFW_OPENED));


    glfwTerminate();

}

