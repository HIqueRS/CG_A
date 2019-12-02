#pragma once
#include <GL/glew.h> /* include GLEW and new version of GL on Windows */
#include <GLFW/glfw3.h> /* GLFW helper library */
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/common.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>

using namespace std;

class Curva
{
public:

	Curva();
	~Curva();

	vector<GLfloat> GerarCurva();
	vector<GLfloat> GerarCurvaInterna();
	vector<GLfloat> GerarCurvaExterna();


	GLuint VAO, VBO;
	vector<GLfloat> Control_Points_X;
	vector<GLfloat> Control_Points_Y;

	float inc = 0.2f;

	
	
};

