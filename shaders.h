#pragma once
#include "oglib.h"

class Shaders{ 
public:
    Shaders();
    Shaders(const char *src, int type); 
    unsigned int get_id() const; 
    void use() const;
    void create_program(std::vector<GLuint> &shaders);
    void set_bool(const std::string &name, bool value) const;
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;
    void set_mat4(const std::string &name, float *value) const;
    void delete_shaders(std::vector<GLuint> &shaders);


private:
    unsigned int ID;

    std::string load_shader(const char *source_file)const; 
    void check_linking_error(GLuint program);
    void check_shader_compilation(GLuint shader);
};



