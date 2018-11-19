//these are constants and libraries that are used by many parts of the program
#include<iostream>
#include<thread>
#include<vector>
#include<map>
#include<string>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#include "../include/GL/glew.h"
#include "../include/GLFW/glfw3.h"
#endif

#include "../include/glm/glm.hpp"
#include "../include/glm/gtx/transform.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"

#define PI 3.14159265358979323846f
#define PI_D 3.14159265358979323846

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef int sint32;
typedef short sint16;
typedef char sint8;

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
