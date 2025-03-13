
#version 330 core 
out vec4 color;
in vec2 TexCoord;

uniform sampler2D texture;
uniform vec4 u_color;
uniform vec2 u_center;
uniform float radius;
uniform vec2 resolution;

void main()
{
    vec2 point = gl_FragCoord.xy / resolution;
    float dis = length( point - u_center);
    if( dis <= radius) 
        color = texture(texture, TexCoord);
    else 
        discard;

}
