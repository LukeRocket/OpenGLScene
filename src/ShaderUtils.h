#pragma once
#ifndef SHADER_UTILS_H_
#define SHADER_UTILS_H_
#include <glad.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

std::string readShaderFile_(const char* path);

void testShader(unsigned int shader, std::string errorMsg = "ERROR::SHADER\n");
#endif