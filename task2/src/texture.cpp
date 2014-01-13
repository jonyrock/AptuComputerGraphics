#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GL/glfw.h>
#include <Magick++.h>
#include <Magick++/Exception.h>
#include <Magick++/Geometry.h>
#include <Magick++/Geometry.h>
#include <iostream>


using namespace Magick;
using namespace std;

GLuint loadBMP(const char* imagepath) {

    printf("Reading image %s\n", imagepath);

    // Data read from the header of the BMP file
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    unsigned int width, height;
    // Actual RGB data
    unsigned char * data;

    // Open the file
    FILE * file = fopen(imagepath, "rb");
    if (!file) {
        printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath);
        getchar();
        return 0;
    }

    // Read the header, i.e. the 54 first bytes

    // If less than 54 bytes are read, problem
    if (fread(header, 1, 54, file) != 54) {
        printf("Not a correct BMP file\n");
        return 0;
    }
    // A BMP files always begins with "BM"
    if (header[0] != 'B' || header[1] != 'M') {
        printf("Not a correct BMP file\n");
        return 0;
    }
    // Make sure this is a 24bpp file
    if (*(int*) &(header[0x1E]) != 0) {
        printf("Not a correct BMP file\n");
        return 0;
    }
    if (*(int*) &(header[0x1C]) != 24) {
        printf("Not a correct BMP file\n");
        return 0;
    }

    // Read the information about the image
    dataPos = *(int*) &(header[0x0A]);
    imageSize = *(int*) &(header[0x22]);
    width = *(int*) &(header[0x12]);
    height = *(int*) &(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0) imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0) dataPos = 54; // The BMP header is done that way

    // Create a buffer
    data = new unsigned char [imageSize];

    // Read the actual data from the file into the buffer
    size_t fr4 = fread(data, 1, imageSize, file);

    // Everything is in memory now, the file wan be closed
    fclose(file);

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    // OpenGL has now copied the data. Free our own version
    delete [] data;

    // Return the ID of the texture we just created
    return textureID;
}

GLuint loadJPEG(const char* filename) {

    Image image;
    GLfloat * data;
    try {

        image.read(filename);

        // Create one OpenGL texture
        GLuint textureID;
        glGenTextures(1, &textureID);

        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, textureID);

        size_t imageSize = image.size().width() * image.size().height() * 3;

        data = new GLfloat[imageSize];
        size_t dataPtr = 0;
        for (size_t i = 0; i < image.size().width(); i++) {
            for (size_t j = 0; j < image.size().height(); j++) {
                ColorRGB rgb(image.pixelColor(i, j));
                data[dataPtr++] = (GLfloat)rgb.red();
                data[dataPtr++] = (GLfloat)rgb.green();
                data[dataPtr++] = (GLfloat)rgb.blue();
            }
        }

        // Give the image to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                image.size().width(), image.size().height(),
                0, GL_RGB, GL_FLOAT, data);

        delete [] data;
        // Return the ID of the texture we just created
        return textureID;

    } catch (Exception &error_) {
        cout << "Caught exception: " << error_.what() << endl;
        return 1;
    }
    return 0;

}


