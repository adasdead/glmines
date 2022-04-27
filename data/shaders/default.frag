#version 330 core

in vec2 tex_coords;

uniform sampler2D image;
uniform bool is_hover;

void main()
{    
    if (is_hover)
        gl_FragColor = mix(texture(image, tex_coords), vec4(1.0f), 0.5f);
    else
        gl_FragColor = texture(image, tex_coords);
}  