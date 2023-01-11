#include "program.hh"

static std::string loadText(const std::string& filename) {
    std::ifstream inputSrcFfile(filename, std::ios::in);
    std::string line;
    std::string fileContent = "";
    if (inputSrcFfile.fail()) {
        std::cerr << "FAIL\n";
        return "";
    }
    while (getline(inputSrcFfile, line)) {
        fileContent = fileContent + line + "\n";
    }
    fileContent += '\0';
    inputSrcFfile.close();
    return fileContent;
}

void Program::loadShaders(const std::string& vertShaderPath, const std::string& fragShaderPath) {
    std::string vertSrc = loadText(vertShaderPath);
    std::string fragSrc = loadText(fragShaderPath);
    char* vertSrcData = (char*)std::malloc(vertSrc.length() * sizeof(char));
    char* fragSrcData = (char*)std::malloc(fragSrc.length() * sizeof(char));
    vertSrc.copy(vertSrcData, vertSrc.length());
    fragSrc.copy(fragSrcData, fragSrc.length());
    this->shaderId.push_back(glCreateShader(GL_VERTEX_SHADER));
    this->shaderId.push_back(glCreateShader(GL_FRAGMENT_SHADER));
    glShaderSource(this->shaderId[0], 1, (const GLchar**)&(vertSrcData), 0);
    glShaderSource(this->shaderId[1], 1, (const GLchar**)&(fragSrcData), 0);

    GLint compileStatus = GL_TRUE;
    for (size_t i = 0; i < this->shaderId.size(); i++) {
        glCompileShader(this->shaderId[i]);
        glGetShaderiv(this->shaderId[i], GL_COMPILE_STATUS, &compileStatus);
        if (compileStatus != GL_TRUE) {
            std::cout << "Shader compile failed\n";
            GLint log_size;
            char* shader_log;
            glGetShaderiv(this->shaderId[i], GL_INFO_LOG_LENGTH, &log_size);
            shader_log =
                (char*)std::malloc(log_size); /* +1 pour le caractere de fin de chaine '\0' */
            if (shader_log != 0) {
                glGetShaderInfoLog(this->shaderId[i], log_size, &log_size, shader_log);
                std::cerr << "SHADER " << i << " : " << shader_log << std::endl;
            }
            std::free(shader_log);
            std::free(vertSrcData);
            std::free(fragSrcData);
            throw std::runtime_error("Shader compilation fail");
        }
    }
    std::free(vertSrcData);
    std::free(fragSrcData);
}

void Program::loadShaders(const std::string& vertShaderPath, const std::string& tescShaderPath,
                          const std::string& teseShaderPath, const std::string& fragShaderPath) {
    std::string vertSrc = loadText(vertShaderPath);
    std::string tescSrc = loadText(tescShaderPath);
    std::string teseSrc = loadText(teseShaderPath);
    std::string fragSrc = loadText(fragShaderPath);
    char* vertSrcData = (char*)std::malloc(vertSrc.length() * sizeof(char));
    char* tescSrcData = (char*)std::malloc(tescSrc.length() * sizeof(char));
    char* teseSrcData = (char*)std::malloc(teseSrc.length() * sizeof(char));
    char* fragSrcData = (char*)std::malloc(fragSrc.length() * sizeof(char));
    vertSrc.copy(vertSrcData, vertSrc.length());
    tescSrc.copy(tescSrcData, tescSrc.length());
    teseSrc.copy(teseSrcData, teseSrc.length());
    fragSrc.copy(fragSrcData, fragSrc.length());
    this->shaderId.push_back(glCreateShader(GL_VERTEX_SHADER));
    this->shaderId.push_back(glCreateShader(GL_TESS_CONTROL_SHADER));
    this->shaderId.push_back(glCreateShader(GL_TESS_EVALUATION_SHADER));
    this->shaderId.push_back(glCreateShader(GL_FRAGMENT_SHADER));
    glShaderSource(this->shaderId[0], 1, (const GLchar**)&(vertSrcData), 0);
    glShaderSource(this->shaderId[1], 1, (const GLchar**)&(tescSrcData), 0);
    glShaderSource(this->shaderId[2], 1, (const GLchar**)&(teseSrcData), 0);
    glShaderSource(this->shaderId[3], 1, (const GLchar**)&(fragSrcData), 0);

    GLint compileStatus = GL_TRUE;
    for (size_t i = 0; i < this->shaderId.size(); i++) {
        glCompileShader(this->shaderId[i]);
        glGetShaderiv(this->shaderId[i], GL_COMPILE_STATUS, &compileStatus);
        if (compileStatus != GL_TRUE) {
            std::cout << "Shader compile failed\n";
            GLint log_size;
            char* shader_log;
            glGetShaderiv(this->shaderId[i], GL_INFO_LOG_LENGTH, &log_size);
            shader_log =
                (char*)std::malloc(log_size); /* +1 pour le caractere de fin de chaine '\0' */
            if (shader_log != 0) {
                glGetShaderInfoLog(this->shaderId[i], log_size, &log_size, shader_log);
                std::cerr << "SHADER " << i << " : " << shader_log << std::endl;
            }
            std::free(shader_log);
            std::free(vertSrcData);
            std::free(fragSrcData);
            std::free(tescSrcData);
            std::free(teseSrcData);
            throw std::runtime_error("Shader compilation fail");
        }
    }
    std::free(vertSrcData);
    std::free(fragSrcData);
    std::free(tescSrcData);
    std::free(teseSrcData);
}

void Program::loadShaders(const std::string& vertShaderPath, const std::string& tescShaderPath,
                          const std::string& teseShaderPath, const std::string& geomShaderPath, const std::string& fragShaderPath) {
    std::string vertSrc = loadText(vertShaderPath);
    std::string tescSrc = loadText(tescShaderPath);
    std::string teseSrc = loadText(teseShaderPath);
    std::string geomSrc = loadText(geomShaderPath);
    std::string fragSrc = loadText(fragShaderPath);
    char* vertSrcData = (char*)std::malloc(vertSrc.length() * sizeof(char));
    char* tescSrcData = (char*)std::malloc(tescSrc.length() * sizeof(char));
    char* teseSrcData = (char*)std::malloc(teseSrc.length() * sizeof(char));
    char* geomSrcData = (char*)std::malloc(geomSrc.length() * sizeof(char));
    char* fragSrcData = (char*)std::malloc(fragSrc.length() * sizeof(char));
    vertSrc.copy(vertSrcData, vertSrc.length());
    tescSrc.copy(tescSrcData, tescSrc.length());
    teseSrc.copy(teseSrcData, teseSrc.length());
    geomSrc.copy(geomSrcData, geomSrc.length());
    fragSrc.copy(fragSrcData, fragSrc.length());
    this->shaderId.push_back(glCreateShader(GL_VERTEX_SHADER));
    this->shaderId.push_back(glCreateShader(GL_TESS_CONTROL_SHADER));
    this->shaderId.push_back(glCreateShader(GL_TESS_EVALUATION_SHADER));
    this->shaderId.push_back(glCreateShader(GL_GEOMETRY_SHADER));
    this->shaderId.push_back(glCreateShader(GL_FRAGMENT_SHADER));
    glShaderSource(this->shaderId[0], 1, (const GLchar**)&(vertSrcData), 0);
    glShaderSource(this->shaderId[1], 1, (const GLchar**)&(tescSrcData), 0);
    glShaderSource(this->shaderId[2], 1, (const GLchar**)&(teseSrcData), 0);
    glShaderSource(this->shaderId[3], 1, (const GLchar**)&(geomSrcData), 0);
    glShaderSource(this->shaderId[4], 1, (const GLchar**)&(fragSrcData), 0);

    GLint compileStatus = GL_TRUE;
    for (size_t i = 0; i < this->shaderId.size(); i++) {
        glCompileShader(this->shaderId[i]);
        glGetShaderiv(this->shaderId[i], GL_COMPILE_STATUS, &compileStatus);
        if (compileStatus != GL_TRUE) {
            std::cout << "Shader compile failed\n";
            GLint log_size;
            char* shader_log;
            glGetShaderiv(this->shaderId[i], GL_INFO_LOG_LENGTH, &log_size);
            shader_log =
                (char*)std::malloc(log_size); /* +1 pour le caractere de fin de chaine '\0' */
            if (shader_log != 0) {
                glGetShaderInfoLog(this->shaderId[i], log_size, &log_size, shader_log);
                std::cerr << "SHADER " << i << " : " << shader_log << std::endl;
            }
            std::free(shader_log);
            std::free(vertSrcData);
            std::free(fragSrcData);
            std::free(tescSrcData);
            std::free(teseSrcData);
            std::free(geomSrcData);
            throw std::runtime_error("Shader compilation fail");
        }
    }
    std::free(vertSrcData);
    std::free(fragSrcData);
    std::free(tescSrcData);
    std::free(teseSrcData);
    std::free(geomSrcData);
}

void Program::linkProgram(void) {
    GLint linkStatus = GL_TRUE;
    this->programId = glCreateProgram();
    if (this->programId == 0) throw std::runtime_error("Program create fail");
    for (size_t i = 0; i < this->shaderId.size(); i++) {
        glAttachShader(programId, this->shaderId[i]);
    }
    glLinkProgram(programId);
    glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        std::cout << "Shader link failed\n";
        GLint log_size;
        char* program_log;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &log_size);
        program_log = (char*)std::malloc(log_size); /* +1 pour le caractere de fin de chaine '\0' */
        if (program_log != 0) {
            glGetProgramInfoLog(programId, log_size, &log_size, program_log);
            std::cerr << "Program " << program_log << std::endl;
        }
        std::free(program_log);
        throw std::runtime_error("Shader link fail");
    }
}