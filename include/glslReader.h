#ifndef GLSLREADER_H 
#define GLSLREADER_H 
#include <sys/stat.h>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class glslReader {
	public:
		glslReader();

		//int readFile(char filename[255]);
		string readFile(const char* filename);
	private:
		off_t GetFileLength(std::string const& filename);
};

#endif
