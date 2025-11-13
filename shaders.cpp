#include "shaders.h"
#include "oglib.h"


Shaders::Shaders() : ID(0) {}

Shaders::Shaders(const char *src, int type ){
    ID = glCreateShader(type);    
    std::string src_shader = load_shader(src);
    const char *source = src_shader.c_str();
    glShaderSource(ID, 1, &source, NULL);
    glCompileShader(ID);
    check_shader_compilation(ID);
}

unsigned int Shaders::get_id() const{
    return ID;
}

void Shaders::use() const {
   glUseProgram(ID); 
}

std::string Shaders::load_shader(const char *source_file) const
{
    std::ostringstream src;
    std::fstream file;
    file.open(source_file);
    if(!file){
        std::cerr << "ERROR: Cannot open shader file [" << source_file <<"]\n" ;
        return std::string();
    }
    src << file.rdbuf();
    return src.str();    
}

void Shaders::create_program(std::vector<GLuint> &shaders)
{
    ID = glCreateProgram();
    for(auto shader : shaders ){
        glAttachShader(ID, shader); 
    }
    glLinkProgram(ID); 
    check_linking_error(ID);
    delete_shaders(shaders);
}

void Shaders::delete_shaders(std::vector<GLuint> &shaders){
    for (auto &shader : shaders)
    glDeleteShader(shader);
}

void Shaders::check_linking_error(unsigned int program)
{
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

}

void Shaders::check_shader_compilation(unsigned int shader)
{
    int shader_success;
    char shader_info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_success);
    if(!shader_success){
        glGetShaderInfoLog(shader, 512, NULL, shader_info_log);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << shader_info_log << std::endl;
    }
}

void Shaders::set_bool(const std::string &name, bool value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}

void Shaders::set_int(const std::string &name, int value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shaders::set_float(const std::string &name, float value) const{
    glUniform1f(glGetUniformLocation(ID, name.c_str()),  value);
}

void Shaders::set_mat4(const std::string &name, float *value) const{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()),1 ,GL_FALSE, value);
}

