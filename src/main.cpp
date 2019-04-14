#include <iostream>
//NOTE: glad must be included BEFORE glfw so that 
//      glfw can overwrite opengl header calls
//TODO: Swap glad headers to second for distrib.
//      Syntastic sees the proper line as an error.
#include "../include/glslLoader.h"
#include "../include/glad/glad.h"
//#include <glad.h>
#include <GLFW/glfw3.h>
#include "../include/linmath.h"
#include "../include/glslReader.h"

using namespace std;

struct WindowWrapper {
	GLFWwindow* window;
	int width;
	int height;
	const char* name;
	float clear_r;
	float clear_g;
	float clear_b;
	float opacity;
};

WindowWrapper MainWindow;

int main() {
	//start function identities
	int createMainWindow(int windowWidth, int windowHeight, char* windowName);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow *window);
	//end function identities
	

	int windowCreateStatus = createMainWindow(800, 600, (char*)"Hello, world!");
	if (windowCreateStatus == -1) {return -1; };

	//allow buffer to resize with window
	glfwSetFramebufferSizeCallback(MainWindow.window, framebuffer_size_callback);

	//make a triangle
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	glslLoader loader;
	//loader.loadShader((const char*)"shaders/vertex.glsl");
	
	//load and compile the vertex shader
	int fragmentShader = loader.loadShader((const char*)"shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	int vertexShader = loader.loadShader((const char*)"shaders/vertex.glsl", GL_VERTEX_SHADER);

	//add and link shaders
	loader.addShader(vertexShader);
	loader.addShader(fragmentShader);
	loader.linkShaderProgram();

	//clean up
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	//make and bind a buffer ID.
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

	//assign vert array to buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//give opengl vertex data, and how to interpret
	//
	//layout location, vec#, data type, options for 
	//int data type, 'stride'(size of each data type, or 3 floats, where position data starts
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//draw the mesh(prim, start, # of verts)



	//create the main loop
	while(!glfwWindowShouldClose(MainWindow.window))
	{
		//poll for keys every frame
		processInput(MainWindow.window);

		//do stuff
		glClearColor(MainWindow.clear_r, MainWindow.clear_g,
				     MainWindow.clear_b, MainWindow.opacity);
		glClear(GL_COLOR_BUFFER_BIT);

		//finalize
		glUseProgram(loader.getShaderProgram());

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//draw crap on the screen
		glfwSwapBuffers(MainWindow.window);
		glfwPollEvents();
	}

	glfwTerminate();
    return 0;
}


int createMainWindow(int windowWidth, int windowHeight, char* windowName) {
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	//Set all of the initial state for the struct
	MainWindow.width = windowWidth;
	MainWindow.height = windowHeight;
	MainWindow.name = windowName;
	MainWindow.window = glfwCreateWindow(MainWindow.width, MainWindow.height, MainWindow.name, NULL, NULL);
	MainWindow.clear_r = 0.2f;
	MainWindow.clear_g = 0.2f;
	MainWindow.clear_b = 0.2f;
	MainWindow.opacity = 1.0f;

	//GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, NULL);

	int windowCreateStatus = 0;

	if (MainWindow.window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		//return -1;
		windowCreateStatus = -1;
	}
	glfwMakeContextCurrent(MainWindow.window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		//return -1;
		windowCreateStatus = -1;
	}

	glViewport(0,0,MainWindow.width,MainWindow.height);

	return windowCreateStatus;
}

void processInput(GLFWwindow *window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MainWindow.clear_r = 1.0f;
	}
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}  
