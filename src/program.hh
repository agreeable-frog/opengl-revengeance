#pragma once

#include <fstream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Program {
public:
    GLuint programId;
    GLuint shaderId[2];
    void loadShaders(const std::string&, const std::string&);
    void linkProgram(void);
};