#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in)
        return {};

    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    if (vertexCode.empty() || fragmentCode.empty())
    {
        std::cerr << "Failed to read shader file(s)\n";
        return;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // дальше: glCreateShader, glShaderSource, glCompileShader, etc.
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);


    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
void Shader::Activate()
{
    glUseProgram(ID);
}
void Shader::Delete()
{
    glDeleteProgram(ID);
}