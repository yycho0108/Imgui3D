#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
//uniform sampler2D texture1;

void main()
{    
    //FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    //FragColor = vec4(TexCoords.x, TexCoords.y, 0.0, 1.0);
    //FragColor = texture(texture1, TexCoords);
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    FragColor = vec4(TexCoords.x, TexCoords.y, 1.0f, 1.0f);
}
