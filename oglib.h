#pragma once 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <iterator>
#include <vector>
#include <sstream>
#include <string>
#include <vector>
#include <array>

#include "shaders.h"
#include "textures.h"


#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define BG_COLOR  .2,.2,.2,1.
#define VERT_CAP 255
#define IND_CAP 255

GLFWwindow* init();
void framebuffer_size_callback(GLFWwindow *window, int width, int height);



class Shape{
public:
    void MakeCube();
    void MakeCercil(); 
    int ver_size()const;
    int ind_size()const;

    std::array<float, VERT_CAP> vertices;
    std::array<unsigned int, IND_CAP> indeces;

};

