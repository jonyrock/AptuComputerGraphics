#include "objloader.h"
#include "shader.h"

#include "figures/geom.h"
#include "figures/textures.h"
#include "camera.h"
#include "lightNavigation.h"


#include <GL/glfw.h>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <glm/gtx/transform.hpp>

using namespace std;
using namespace glm;

int GLinit() {


    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

    if (!glfwOpenWindow(1024, 768, 0, 0, 0, 0, 32, 0, GLFW_WINDOW)) {
        cerr << "Failed to open GLFW window." << endl;
        glfwTerminate();
        return -1;
    }
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW" << endl;
        return -1;
    }

    glfwSetWindowTitle("Bunny party");
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
    GLuint mvId = glGetUniformLocation(programId, "MV");
    GLuint colorId = glGetUniformLocation(programId, "vertexColor");
    GLuint viewerPosId = glGetUniformLocation(programId, "viewerPos");

    // Attributes
    glUseProgram(programId);

    // View init
    Camera camera(0, 10, 12);
    LightNavigation lightNavigation(programId);

    // Projection init
    mat4 Model;
    mat4 View;
    float NEAR_CLIPPING_PLANE = 0.1f;
    float FAR_CLIPPING_PLANE = 100.0f;
    mat4 Projection = perspective(45.0f, 4.0f / 3.0f, NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE);

    mat4 MVP;
    mat4 MV;

    /** PLANE INIT **/
    vector<vec3> planeVertives;
    vector<vec3> planeNormals;
    fillPlane(planeVertives);
    mat4 planeModel = rotate(mat4(10.0f), 90.f, vec3(1, 0, 0));
    for (int i = 0; i < planeVertives.size(); i++) {
        auto mv = planeModel * vec4(planeVertives[i], 1.f);
        planeVertives[i] = vec3(mv[0], mv[1], mv[2]);
    }
    for (int i = 0; i < planeVertives.size(); i++) {
        planeNormals.push_back(vec3(0, 1, 0));
    }


    GLuint planeVerticesBuffer;
    glGenBuffers(1, &planeVerticesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, planeVerticesBuffer);
    glBufferData(GL_ARRAY_BUFFER, planeVertives.size() * sizeof (vec3), &planeVertives[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    GLuint planeNormalsBuffer;
    glGenBuffers(1, &planeNormalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, planeNormalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, planeNormals.size() * sizeof (vec3), &planeNormals[0], GL_STATIC_DRAW);


    /** RABBIT INIT **/
    vector<vec3> rabbitVertices;
    vector<vec3> rabbitNormals;

    if (!loadOBJ("resources/bunny_n.obj", rabbitVertices, rabbitNormals)) {
        return -1;
    }

    mat4 rabbitModel = mat4(30.0f);
    for (int i = 0; i < rabbitVertices.size(); i++) {
        auto mv = rabbitModel * vec4(rabbitVertices[i], 1.f);
        rabbitVertices[i] = vec3(mv[0], mv[1], mv[2]);
    }

    GLuint rabbitVertecesBuffer;
    glGenBuffers(1, &rabbitVertecesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, rabbitVertecesBuffer);
    glBufferData(GL_ARRAY_BUFFER, rabbitVertices.size() * sizeof (vec3), &rabbitVertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint rabbitNormalsBuffer;
    glGenBuffers(1, &rabbitNormalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, rabbitNormalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, rabbitNormals.size() * sizeof (vec3), &rabbitNormals[0], GL_STATIC_DRAW);

    glClearColor(0.9f, 0.9f, 0.9f, 0.0f);

    while (true) {

        camera.windowsIterate();
        camera.updateView(View);
        
        lightNavigation.windowsIterate();

        MVP = Projection * View * Model;
        MV = View * Model;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(mvpId, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(mvId, 1, GL_FALSE, &MV[0][0]);
        
        vec3 viewerPos = camera.viewerPos();
        glUniform3f(viewerPosId, viewerPos.x, viewerPos.y, viewerPos.z); 

        /** PLANE **/
        glUniform3f(colorId, 0.9f, 0.9f, 0.9f);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, planeVerticesBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, planeNormalsBuffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        
        glDrawArrays(GL_TRIANGLES, 0, 2 * 3);


        /** RABBIT **/
        glUniform3f(colorId, 184.f / 255, 47.f / 255, 196.f / 255);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, rabbitVertecesBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, rabbitNormalsBuffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        glDrawArrays(GL_TRIANGLES, 0, rabbitVertices.size() * 3);


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

