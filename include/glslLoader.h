#ifndef GLSLLOADER_H 
#define GLSLLOADER_H 

#include <iostream>

class glslLoader {
	public:
		glslLoader();

		//int loadShader(const char* filename);
		int loadShader(const char* filename, int shaderType);
		int loadShaderWithSource(const char* filename, const char* source);
		void addShader(int shader);
		void linkShaderProgram();
		unsigned int getShaderProgram();
	private:
};

#endif
