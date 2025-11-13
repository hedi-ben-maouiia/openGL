#include "oglib.h"



GLFWwindow* init(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
    if(window == NULL){
        std::cout << "Failed to create GLFW window\n" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD\n" << std::endl;
        return NULL;
    }
    glViewport(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return window;
}

void Shape::MakeCube(){
    vertices =  {
        // Back Face 
        -0.5, -0.5, -0.5,       0.0, 0.0,                        // BL -> 0
         0.5, -0.5, -0.5,       1.0, 0.0,                        // BR -> 1
         0.5,  0.5, -0.5,       1.0, 1.0,                        // TR -> 2
        -0.5,  0.5, -0.5,       0.0, 1.0,                        // TL -> 3        
        // Front Face
        -0.5, -0.5, 0.5,        0.0, 0.0,                        // BL -> 4
         0.5, -0.5, 0.5,        1.0, 0.0,                        // BR -> 5
         0.5,  0.5, 0.5,        1.0, 1.0,                        // TR -> 6
        -0.5,  0.5, 0.5,        0.0, 1.0,                        // TL -> 7 
        // Left Face
        -0.5, -0.5, -0.5,        0.0, 0.0,                        // BL -> 8
        -0.5, -0.5,  0.5,        1.0, 0.0,                        // BR -> 9
        -0.5,  0.5,  0.5,        1.0, 1.0,                        // TR -> 10
        -0.5,  0.5, -0.5,        0.0, 1.0,                        // TL -> 11 
        // Right Face
        0.5, -0.5, -0.5,        0.0, 0.0,                        // BL -> 12
        0.5, -0.5,  0.5,        1.0, 0.0,                        // BR -> 13
        0.5,  0.5,  0.5,        1.0, 1.0,                        // TR -> 14
        0.5,  0.5, -0.5,        0.0, 1.0,                        // TL -> 15 
        
        // Bottom Face
        -0.5, -0.5, -0.5,        0.0, 0.0,                        // BL -> 16 
         0.5, -0.5, -0.5,        1.0, 0.0,                        // BR -> 17 
         0.5, -0.5,  0.5,        1.0, 1.0,                        // TR -> 18 
        -0.5, -0.5,  0.5,        0.0, 1.0,                        // TL -> 19

        // Top Face
        -0.5, 0.5, -0.5,        0.0, 0.0,                        // BL -> 16 
         0.5, 0.5, -0.5,        1.0, 0.0,                        // BR -> 17 
         0.5, 0.5,  0.5,        1.0, 1.0,                        // TR -> 18 
        -0.5, 0.5,  0.5,        0.0, 1.0,                        // TL -> 19  
    };    
    indeces = {
        0, 1, 2, 2, 3, 0,        // back
        4, 5, 6, 6, 7, 4,        // front
        8, 9, 10, 10, 11, 8,     // left
        12, 13, 14, 14, 15, 12,  // right 
        16, 17, 18, 18, 19, 16,  // bottom 
        20, 21, 22, 22, 23, 20,  // top 
    };

}
int Shape::ver_size() const{
    return vertices.size() * sizeof(float);
}

int Shape::ind_size()const{
    return indeces.size() * sizeof(unsigned int);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0,0,width, height);
}



