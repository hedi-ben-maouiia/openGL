#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "shaders.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define WIDTH 720
#define HEIGHT 480
#define VERTEX_FILE   "vertex.glsl" 
#define FRAGMENT_FILE "fragment.glsl"

time_t getLastModificationTime(const std::string& filePath) {
    struct stat result;
    if (stat(filePath.c_str(), &result) == 0) {
        return result.st_mtime;
    }
    return 0;
}

struct mousPos{
    float x; 
    float y;
};
mousPos getMousePos(GLFWwindow* window)
{
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    float xpos = (xPos / width);
    float ypos = (height - yPos) / height;
    return {xpos, ypos};
}
static float radius = 50.f;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

    if(yoffset > 0 && radius < 1.0)
        radius += 0.08;
    else if(yoffset < 0 && radius > 0.1)
        radius -= 0.08;
}
void RenderCircel(std::vector<float>& vertices,const int segments,float &radius, float xPos, float yPos)
{
    vertices.clear(); 
    vertices.reserve((segments + 2) * 2);
    const float PI = 3.14159265359f;  
    vertices.push_back(xPos);
    vertices.push_back(yPos);

    for(int i = 0; i <= segments; i++){
        float angle = (2.0f * PI * i) / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        vertices.push_back(x);
        vertices.push_back(y);
    }
}
void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
}
int main(void)
{
    if(!glfwInit()){
        std::cerr << "Cannot initialize GLFW\n";
        glfwTerminate();
        exit(-1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", nullptr, nullptr);
    if(!window){
    std::cerr << "Faild to create GLFW window\n";
    glfwTerminate();
    exit(-1);
    }

    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to initialize GLAD\n";
        exit(-1);
    }
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0,width, height);
    
    glfwSetScrollCallback(window, scroll_callback);

    /* 
    const int segment = 100;
    std::vector<float> vertices;
    RenderCircel(vertices, segment, radius, 0.f, 0.f);
    */

    float vertices[] = {
        // Positions        // Texture Coordinates
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,  // Bottom left
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f,  // Bottom right
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f,  // Top right
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f   // Top left
    };

    uint32_t VAO,VBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /*
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),  vertices.data(), GL_STATIC_DRAW); 
    */
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int texWidth, texHeight, nrChannel;
    unsigned char *data = stbi_load("/home/kira/wallpaper/earth.jpg", &texWidth, &texHeight, &nrChannel,0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "Faild to load texture\n";
        return -1;
    }
    stbi_image_free(data);

    Shader sh(VERTEX_FILE,FRAGMENT_FILE);
    glUseProgram(sh.getProgram());
    time_t vertexLastModified = getLastModificationTime(VERTEX_FILE);
    time_t fragmentLastModified = getLastModificationTime(FRAGMENT_FILE);

    int radiusLocation =    glGetUniformLocation(sh.getProgram(), "radius");
    int colorLocation  =    glGetUniformLocation(sh.getProgram(),"u_color");
    int centerLocation =    glGetUniformLocation(sh.getProgram(), "u_center");
    int resolutionLocation= glGetUniformLocation(sh.getProgram(), "resolution");
    int textureLocation = glGetUniformLocation(sh.getProgram(), "texture");
    glUniform1i(textureLocation, 0);
    static int frameCount = 0;
    static int reloadInterval = 10; // Reload every 10 frames 
    while (!glfwWindowShouldClose(window)) {

        if (++frameCount % reloadInterval == 0) {
                time_t currentVertexModified   = getLastModificationTime(VERTEX_FILE);
                time_t currentFragmentModified = getLastModificationTime(FRAGMENT_FILE);

            if (currentVertexModified != vertexLastModified || currentFragmentModified != fragmentLastModified) {
                sh.ReloadShaders(VERTEX_FILE, FRAGMENT_FILE);
                vertexLastModified = currentVertexModified;
                fragmentLastModified = currentFragmentModified;
            }
        }

        mousPos mp = getMousePos(window);
        float time = glfwGetTime();
        float red  = (sin(time)  / 2.0f) + 0.5f;
        float green= (cos(time)  / 2.0f) + 0.5f;
        
        glUniform2f(resolutionLocation, (float)width, (float)height);
        glUniform4f(colorLocation, red, green, 0.2f, 1.0f);
        glUniform2f(centerLocation,mp.x, mp.y);
        glUniform1f(radiusLocation, radius / (float)width);

        glClear(GL_COLOR_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D,texture);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
    }
