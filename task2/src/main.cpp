#include "shader.h"
#include "figures/geom.h"
#include "figures/colors.h"
#include "camera.h"

#include <GL/glfw.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace glm;

typedef unsigned char uchar;

int GLinit() {
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

    glfwSetWindowTitle("Geometry party");
    glfwEnable(GLFW_STICKY_KEYS);

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    return 0;

}

int main(void) {

    if (GLinit() != 0) {
        return 1;
    }

    // GLSL init
    GLuint programId = LoadShaders("src/simple.vert", "src/simple.frag");

    // Uniform
    GLuint mvpId = glGetUniformLocation(programId, "MVP");
    GLuint isWireframeId = glGetUniformLocation(programId, "isWireframe");
    GLuint nearClippingPlaneId = glGetUniformLocation(programId, "nearClippingPlaneId");
    GLuint farClippingPlaneId = glGetUniformLocation(programId, "farClippingPlaneId");

    // Attributes
    GLuint vertexPosition_modelspaceID = glGetAttribLocation(programId, "vertexPosition_modelspace");
    GLuint vertexColorId = glGetAttribLocation(programId, "vertexColor");

    glUseProgram(programId);

    // Model init
    mat4 Model;
    vector<vec3> vertices;
    vector<vec3> verticesColor;
    fillCube(vertices);
    fillCubeColor(verticesColor);

    // View init
    mat4 View;
    Camera camera(6, 0, 10);

    // Projection init
    float NEAR_CLIPPING_PLANE = 0.1f;
    float FAR_CLIPPING_PLANE = 100.0f;
    mat4 Projection = perspective(45.0f, 4.0f / 3.0f, NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE);
    glUniform1f(nearClippingPlaneId, NEAR_CLIPPING_PLANE);
    glUniform1f(farClippingPlaneId, FAR_CLIPPING_PLANE);

    mat4 MVP;

    // GPU buffers init
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof (vec3), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    vector<vec3> g_color_buffer_data;
    fillCubeColor(g_color_buffer_data);
    
    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof (vec3), &g_color_buffer_data[0], GL_STATIC_DRAW);


    glClearColor(0.9f, 0.9f, 0.9f, 0.0f);

    while (true) {

        camera.windowsIterate();
        camera.updateView(View);

        MVP = Projection * View * Model;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(mvpId, 1, GL_FALSE, &MVP[0][0]);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableVertexAttribArray(vertexColorId);
        glVertexPointer(2, GL_FLOAT, 0, &verticesColor[0]);
        glVertexAttribPointer(vertexPosition_modelspaceID, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        // 2nd attribute buffer : colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
                1, // attribute. No particular reason for 1, but must match the layout in the shader.
                3, // size
                GL_FLOAT, // type
                GL_FALSE, // normalized?
                0, // stride
                (void*) 0 // array buffer offset
                );

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

        glDisableVertexAttribArray(vertexPosition_modelspaceID);


        glfwSwapBuffers();

        if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
            break;
        if (!glfwGetWindowParam(GLFW_OPENED))
            break;

    }

    glDeleteProgram(programId);
    glfwTerminate();

}

