#include "oglib.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Textures::Textures(int type){
    glGenTextures(1, &ID); 
    glBindTexture(type, ID);
}

void Textures::texture_wrapping_option(int type, int option){
    glTexParameteri(type, GL_TEXTURE_WRAP_S, option);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, option);
}

void Textures::texture_filtering_option(int type, int option){
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, option);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, option);
}
void Textures::set_border_color_option(float *borderColor)
{
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
}
void Textures::generate_text_img(int type, const char *img_path,ImgType t){
    int color_type = GL_RGB; 

    if(t == PNG)
        color_type = GL_RGBA;
    else if(t == JPG)
        color_type = GL_RGB;

    int w, h, nr_channels; 
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(img_path, &w, &h, &nr_channels, 0); 
    if(data){
        glTexImage2D(type, 0, GL_RGB,w, h, 0, color_type,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(type);
    }
    else
        std::cout << "Failed to load texture" << std::endl;

    stbi_image_free(data);
}

unsigned int Textures::get_id() const{
    return ID;
}






