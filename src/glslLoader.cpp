#include "../include/glslReader.h"
#include "../include/glslLoader.h"
#include <iostream>
#include "../include/glad/glad.h"
//#include <glad.h>
#include <GLFW/glfw3.h>
#include <cerrno>

using namespace std;

unsigned int shaderProgram;

glslLoader::glslLoader() {
	cout << "created loader\n\n";

	//create the shader object
	shaderProgram = glCreateProgram();
}

unsigned int glslLoader::getShaderProgram() {
	return shaderProgram;
}

void glslLoader::linkShaderProgram() {
	glLinkProgram(shaderProgram);

	//check the program for linking errors
	int success;
    char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::LINKING_FAILED\n" << infoLog << std::endl;
		std::cerr << endl;
	} else {
		std::cout << "Shaders have been linked successfully" << endl;
	}
}

void glslLoader::addShader(int shader) {
	glAttachShader(shaderProgram, shader);
	//glAttachShader(shaderProgram, fragmentShader);
}

//int glslReader::readFile(char filename[255]) {
int glslLoader::loadShader(const char* filename, int shaderType) {
	//read shader file
	glslReader reader;

	string shaderSourceTxt;
	const char* shaderSource;

	shaderSourceTxt = reader.readFile(filename);
	shaderSource = shaderSourceTxt.c_str();
	//shaderSource = reader.readFile(filename);

	cout << "About to print shader source again: " << shaderSource << endl;

	//load and compile shader
	int shader = glCreateShader(shaderType);
	//int shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

	//check success of loading the shader
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << std::endl;
		std::cout << "Failed to load shader " << filename << endl;
		std::cout << infoLog << std::endl;

	} else {
		std::cout << filename << " has been loaded successfully!" << endl;
	}

	return shader;
}

int glslLoader::loadShaderWithSource(const char* filename, const char* source) {
	//read shader file
	glslReader reader;

	const char* shaderSource;

	shaderSource = source;

	cout << "About to print shader source again: " << shaderSource << endl;

	//load and compile shader
	int shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

	//check success of loading the shader
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << std::endl;
		std::cout << "Failed to load shader " << filename << endl;
		std::cout << infoLog << std::endl;

	} else {
		std::cout << filename << " has been loaded successfully!" << endl;
	}

	return shader;
}
