#include "shader.h"
#include "texture.h"
#include "figures/geom.h"
#include "figures/textures.h"
#include "camera.h"
#include "textureNavigation.h"


#include <GL/glfw.h>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>


using namespace std;
using namespace glm;

typedef unsigned char uchar;

int GLinit() {

    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
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
    GLuint textureScaleId = glGetUniformLocation(programId, "textureScale");
    GLuint TextureID = glGetUniformLocation(programId, "myTextureSampler");

    // Attributes
    glUseProgram(programId);

    GLuint Texture = loadJPEG("resources/lenna_head.jpg");

    // View init
    
    Camera camera(6, 0, 10);
    TextureNavigation textureNavigation(TextureID, textureScaleId);

    // Projection init
    mat4 Model;
    mat4 View;
    float NEAR_CLIPPING_PLANE = 0.1f;
    float FAR_CLIPPING_PLANE = 100.0f;
    mat4 Projection = perspective(45.0f, 4.0f / 3.0f, NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE);

    mat4 MVP;

    /** PLANE INIT **/
    vector<vec3> verticesPlane;
    vector<vec2> verticesPlaneUV;
    fillPlane(verticesPlane);
    fillPlaneUV(verticesPlaneUV);

    GLuint vertexPlaneBuffer;
    glGenBuffers(1, &vertexPlaneBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexPlaneBuffer);
    glBufferData(GL_ARRAY_BUFFER, verticesPlane.size() * sizeof (vec3), &verticesPlane[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vertexPlaneBufferUV;
    glGenBuffers(1, &vertexPlaneBufferUV);
    glBindBuffer(GL_ARRAY_BUFFER, vertexPlaneBufferUV);
    glBufferData(GL_ARRAY_BUFFER, verticesPlaneUV.size() * sizeof (vec2), &verticesPlaneUV[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /** CUBE INIT **/
    vector<vec3> verticesCube;
    vector<vec2> verticesCubeUV;
    fillCube(verticesCube);
    fillCubeUV(verticesCubeUV);

    GLuint vertexCubeBuffer;
    glGenBuffers(1, &vertexCubeBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexCubeBuffer);
    glBufferData(GL_ARRAY_BUFFER, verticesCube.size() * sizeof (vec3), &verticesCube[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vertexCubeBufferUV;
    glGenBuffers(1, &vertexCubeBufferUV);
    glBindBuffer(GL_ARRAY_BUFFER, vertexCubeBufferUV);
    glBufferData(GL_ARRAY_BUFFER, verticesCubeUV.size() * sizeof (vec2), &verticesCubeUV[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glClearColor(0.9f, 0.9f, 0.9f, 0.0f);

    int figure = 2;

    while (true) {

        camera.windowsIterate();
        camera.updateView(View);

        textureNavigation.windowsIterate();

        MVP = Projection * View * Model;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(mvpId, 1, GL_FALSE, &MVP[0][0]);

        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture);
        // Set our "myTextureSampler" sampler to user Texture Unit 0
        glUniform1i(TextureID, 0);

        if (glfwGetKey('Z') == GLFW_PRESS)
            figure = 1;

        if (glfwGetKey('X') == GLFW_PRESS)
            figure = 2;

        /** PLANE **/
        if (figure == 1) {
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexPlaneBuffer);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, vertexPlaneBufferUV);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

            glDrawArrays(GL_TRIANGLES, 0, 2 * 3);
        }

        /** CUBE **/
        if (figure == 2) {
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexCubeBuffer);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, vertexCubeBufferUV);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

            glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
        }

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        // Swap buffers
        glfwSwapBuffers();

        if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
            break;
        if (!glfwGetWindowParam(GLFW_OPENED))
            break;

    }

    glDeleteProgram(programId);
    glfwTerminate();

}

