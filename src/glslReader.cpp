#include "../include/glslReader.h"
#include <sys/stat.h>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

glslReader::glslReader() {
	cout << "created reader\n\n";
}

off_t glslReader::GetFileLength(std::string const& filename) {
    struct stat st;
    if (stat(filename.c_str(), &st) == -1)
        throw std::runtime_error(std::strerror(errno));
    return st.st_size;
}

//int glslReader::readFile(char filename[255]) {
//const char* glslReader::readFile(const char* filename) {
string glslReader::readFile(const char* filename) {
	//cout << "is anybody there?";
	ifstream file;
	cout << "\nAttempting to open file: " << filename << endl;
	file.open(filename);

	//if (!file.is_open()) { exit(EXIT_FAILURE); };
	if (!file.is_open()) {
		cout << "Unable to open file successfully.\n";
		//return -1;
	};

	int length = GetFileLength(filename);
	cout << "file length: " << length << endl;

	//TODO: clean up char*, need to pass string
	//      back to main.
	//const char *text = new char[length];
	const char* text = new char[length];

	//file >> text;
	ifstream in(filename);
	string contents((istreambuf_iterator<char>(in)), 
    istreambuf_iterator<char>());

	text = contents.c_str();

	//in theory we shouldn't need to loop
	//through the file. It should create the 
	//needed length to store the entire file
	//in a dynamic character array.
	//cout is a sanity check.

	file.close();

	cout << "attempting to cat the file\n\n";
	cout << text;

	//return text;
	return contents;
}
