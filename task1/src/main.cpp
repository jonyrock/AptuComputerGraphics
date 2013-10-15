#include "shader.hpp"
#include "objloader.hpp"

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/glfw.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

int main(void) {
    
    if (!glfwInit()) { cerr << "Failed to initialize GLFW" << endl;return -1; }

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
    
    if (!glfwOpenWindow(500, 500, 0, 0, 0, 0, 32, 0, GLFW_WINDOW)) {
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
    
    // GLSL init
    GLuint programId = LoadShaders("src/simple.vert", "src/simple.frag");
    GLuint mvpId = glGetUniformLocation(programId, "MVP");
    GLuint vertexColorId = glGetUniformLocation(programId, "vertexColor");
    GLuint vertexPosition_modelspaceID = glGetAttribLocation(programId, "vertexPosition_modelspace");
    
    glUseProgram(programId);
    
    
    // MVP init
    mat4 Projection = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    mat4 View = lookAt(vec3(8, 6, -6), vec3(2, 0, 0), vec3(0, 1, 0));
    mat4 Model = mat4(1.0f);
    mat4 MVP = Projection * View * Model;
    
    // Model init
    vector<vec3> vertices;
    vector<vec2> uvs;
    vector<vec3> normals;
    loadOBJ("resources/model.obj", vertices, uvs, normals);
    
    // GPU buffers init
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof (vec3), &vertices[0], GL_STATIC_DRAW);
    
    glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(mvpId, 1, GL_FALSE, &MVP[0][0]);
        glEnableVertexAttribArray(vertexPosition_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(vertexPosition_modelspaceID, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glUniform3f(vertexColorId, 0.1f, 0.2f, 0.3f);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glUniform3f(vertexColorId, 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        
        glDisableVertexAttribArray(vertexPosition_modelspaceID);
        glfwSwapBuffers();
        
    } while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && 
             glfwGetWindowParam(GLFW_OPENED));
    
    
    glfwTerminate();
    
}

