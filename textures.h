#pragma once
#include "oglib.h"

enum ImgType{
    PNG, 
    JPG
};

class Textures{
public:
    Textures(int type);
    void texture_wrapping_option(int type, int option );
    void texture_filtering_option(int type, int option);
    void set_border_color_option(float *borderColor);
    void generate_text_img(int type, const char *img_path, ImgType t);
    unsigned int get_id() const;
        
private:
    unsigned int ID;
};

