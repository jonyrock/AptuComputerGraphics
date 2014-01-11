#include "shader.h"
#include "figures.h"
#include "camera.h"

#include <iostream>
#include <vector>

#include <GL/glfw.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

using namespace std;
using namespace glm;

typedef unsigned char uchar;

int main(void) {

    mat4 View;
    Camera camera(6, 0, 10);

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

    
    mat4 Model = mat4(0.f);
    Model[0][0] = 1;
    Model[1][1] = 1;
    Model[2][2] = 1;
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
    fillCube(vertices);

    // GPU buffers initEXECFUNCTION
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof (vec3), &vertices[0], GL_STATIC_DRAW);



    glClearColor(0.9f, 0.9f, 0.9f, 0.0f);

    do {
        
        camera.windowsIterate();
        camera.updateView(View);
        
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

