#include "shader.h"
#include "texture.h"
#include "figures/geom.h"
#include "figures/textures.h"
#include "camera.h"


#include <GL/glfw.h>
#include <GL/glew.h>

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

    // Attributes
    glUseProgram(programId);

    // Model init
    mat4 Model;
    vector<vec3> vertices;
    vector<vec2> verticesUV;
    fillCube(vertices);

    // Load the texture using any two methods
//    GLuint Texture = loadBMP("resources/earth_texture_grid.bmp");
    GLuint Texture = loadJPEG("resources/lenna_head.jpg");
    
//    GLuint Texture = loadDDS("resources/uvtemplate.DDS");

    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID = glGetUniformLocation(programId, "myTextureSampler");
    fillCubeUV(verticesUV);

    // View init
    mat4 View;
    Camera camera(6, 0, 10);

    // Projection init
    float NEAR_CLIPPING_PLANE = 0.1f;
    float FAR_CLIPPING_PLANE = 100.0f;
    mat4 Projection = perspective(45.0f, 4.0f / 3.0f, NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE);


    mat4 MVP;

    // GPU buffers init
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof (vec3), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, verticesUV.size() * sizeof (vec2), &verticesUV[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glClearColor(0.9f, 0.9f, 0.9f, 0.0f);

    while (true) {

        camera.windowsIterate();
        camera.updateView(View);

        MVP = Projection * View * Model;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(mvpId, 1, GL_FALSE, &MVP[0][0]);


        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture);
        // Set our "myTextureSampler" sampler to user Texture Unit 0
        glUniform1i(TextureID, 0);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                0, // attribute. No particular reason for 0, but must match the layout in the shader.
                3, // size
                GL_FLOAT, // type
                GL_FALSE, // normalized?
                0, // stride
                (void*) 0 // array buffer offset
                );

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
                1, // attribute. No particular reason for 1, but must match the layout in the shader.
                2, // size : U+V => 2
                GL_FLOAT, // type
                GL_FALSE, // normalized?
                0, // stride
                (void*) 0 // array buffer offset
                );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles

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

