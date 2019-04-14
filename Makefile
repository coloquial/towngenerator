all:
	g++ main.cpp -I /usr/include/GLFW -o hello
run:
	#TODO: uncomment first line. second is for code completion.
	#g++ main.cpp HelloWorldPrinter.cpp -L/usr/lib/ -I/usr/include/GLFW -o hello -lglfw -lGL
	g++ src/main.cpp src/glad.c src/glslReader.cpp src/glslLoader.cpp -L/usr/lib/ -I/usr/include/GLFW -I/usr/include/GL -I./include -I./include/glad -o build/hello -lglfw -lGL -ldl
	
	./build/hello

