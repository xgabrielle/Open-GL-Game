#version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec4 aCol;
    layout (location = 2) in vec2 aTexCoord; // AKA uv
    out vec4 vertexColor;
    out vec4 vertexPos;
    out vec2 texCoord;
    uniform vec2 offset;
    void main()
    {
        gl_Position = vec4(aPos.xyz, 1.0) +vec4(offset.xy,0,0);
        vertexColor = aCol;
        texCoord = aTexCoord;
    }