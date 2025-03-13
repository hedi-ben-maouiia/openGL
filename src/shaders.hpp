#pragma once 
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <sys/stat.h>



class Shader {
public:
    Shader(const std::string &vetFile, const std::string& fragFile){  
        CreateProgram(vetFile, fragFile);
    }
    ~Shader(){ glDeleteProgram(program_id);}
    void         ReloadShaders(const std::string &vertexShader, const std::string &fragmentShader);
    inline unsigned int getProgram(){ return program_id;}


private:
    unsigned int program_id;
    void         CreateProgram(const std::string &vetFile, const std::string& fragFile);
    std::string  LoadShader(const std::string &filePath);
    unsigned int CompileShader(unsigned int type,const std::string &shaderSource);
};

