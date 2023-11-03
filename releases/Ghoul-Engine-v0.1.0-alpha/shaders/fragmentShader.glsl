#version 460 core

out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D texture;
uniform bool useTexture;

void main()
{
    if (useTexture)
    {
        FragColor = texture(texture, TexCoord);
    }
    else
    {
        FragColor = ourColor;
    }
}
