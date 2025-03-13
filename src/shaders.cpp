#include "shaders.hpp"


std::string Shader::LoadShader(const std::string &filePath)
{
    std::ifstream file(filePath); 
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int Shader::CompileShader(unsigned int type,const std::string &shaderSource)
{ 
    unsigned int id = glCreateShader(type);
    const char* src = shaderSource.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    int sucess;
    glGetShaderiv(id, GL_COMPILE_STATUS, &sucess); 
    if (!sucess)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile" 
            << ((type == GL_VERTEX_SHADER) ? "vertex" : "fragment") 
            << " Shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}


void  Shader::CreateProgram(const std::string &vetFile, const std::string& fragFile)
{
    std::string vsource = LoadShader(vetFile);
    std::string fsource = LoadShader(fragFile);
    program_id = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vsource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fsource);
    glAttachShader(program_id, vs);
    glAttachShader(program_id, fs);
    glLinkProgram(program_id);
    glValidateProgram(program_id);
    int success;
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if (!success) {
        int length;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        glGetProgramInfoLog(program_id, length, &length, message);
        std::cerr << "Failed to link shader program!" << std::endl;
        std::cerr << message << std::endl;
        glDeleteProgram(program_id);
        program_id = 0;  // Set to invalid program ID to avoid further usage.
    }
    glDeleteShader(vs);
    glDeleteShader(fs); 

}

void  Shader::ReloadShaders(const std::string &vertexShader, const std::string &fragmentShader)
{ 
    glDeleteProgram(program_id);
    CreateProgram(vertexShader, fragmentShader);
}
