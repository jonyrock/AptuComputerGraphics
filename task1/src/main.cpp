// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <shader.hpp>
#include <objloader.hpp>
#include <vector>

int COUNT = 0;
glm::mat4 get_mvp() {
    
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    
    // Camera matrix
    glm::mat4 View       = glm::lookAt(
                                glm::vec3(4,2,-3), // Camera is at (4,3,3), in World Space
                                glm::vec3(0,0,0), // and looks at the origin
                                glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                           );
    
    
    glm::mat4 Model      = glm::mat4(1.f);
    Model                = glm::rotate(Model, COUNT * 1.0f, glm::vec3(0, 1, 0)); 
    Model                = glm::translate(Model, glm::vec3(-0.5,0,0));
    Model                = glm::scale(Model, glm::vec3(0.4f,0.4f,0.4f));
    glm::mat4 MVP        = Projection * View * Model;
    COUNT++; COUNT = COUNT % 360;
    return MVP;
}

int main( void )
{
    // Initialise GLFW
    if( !glfwInit() ) { fprintf( stderr, "Failed to initialize GLFW\n" ); return -1;}

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2); glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

    // Open a window and create its OpenGL context
    if( !glfwOpenWindow( 600, 300, 0,0,0,0, 32,0, GLFW_WINDOW ) ){ 
        fprintf( stderr, "Failed to open GLFW window.\n" ); glfwTerminate(); return -1; }

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {fprintf(stderr, "Failed to initialize GLEW\n"); return -1;}

    glfwSetWindowTitle( "Task1: Cow model" );
    glfwEnable(GLFW_STICKY_KEYS);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    GLuint programID = LoadShaders( "src/simple.vert", "src/simple.frag" );
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
    GLuint vertexColorID = glGetAttribLocation(programID, "vertexColor");
    

    // #include "cube_data.cpp"
    
    // Read our .obj file
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals; // Won't be used at the moment.
    bool res = loadOBJ("resources/model.obj", vertices, uvs, normals);
    
    
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);
        glm::mat4 mvp = get_mvp();
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
        glEnableVertexAttribArray(vertexPosition_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(vertexPosition_modelspaceID, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        
        // Draw the triangles !
        glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
        
        ////////////////////
        glDisableVertexAttribArray(vertexPosition_modelspaceID);
        glDisableVertexAttribArray(vertexColorID);

        // Swap buffers
        glfwSwapBuffers();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
           glfwGetWindowParam( GLFW_OPENED ) );

    // Cleanup VBO and shader
    // glDeleteBuffers(1, &vertexbuffer);
    glDeleteProgram(programID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

