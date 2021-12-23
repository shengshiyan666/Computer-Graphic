#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>

// Vertex Shader
const char* vertexShaderSource = readTheFile("shader/vertexShaderSource.vert");
const char* lightVertexShaderSource = readTheFile("shader/lightVertexShaderSource.vert");

// Fragment Shader
const char* fragmentShaderSource = readTheFile("shader/fragmentShaderSource.frag");
const char* lightFragmentShaderSource = readTheFile("shader/lightFragmentShaderSource.frag");
