def Settings( **kwargs ):
    return {
        'flags': [ '-x', 'c++', '-L/usr/lib/', '-I/usr/include/GLFW', '-I/usr/include/GL', '-I./include', '-I./include/glad', '-lglfw', '-lGL', '-ldl'],
    }
