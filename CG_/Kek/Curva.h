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
#include <glm/vec2.hpp>

using namespace std;
#define PI 3.14159265

class Curva
{
public:

	Curva();
	~Curva();

	vector<GLfloat> GerarCurva();
	vector<GLfloat> GerarCurvaInterna(vector<GLfloat> Cur, bool q);
	vector<GLfloat> GerarCurvaExterna(vector<GLfloat> Cur);

	void CreateObj();

	ofstream ArqObj;


	GLuint VAO, VBO,VAOI,VAOE,VBOI,VBOE;
	vector<GLfloat> Control_Points_X;
	vector<GLfloat> Control_Points_Y;

	vector<GLfloat> CurvaI;
	vector<GLfloat> CurvaE;

	float inc = 0.4f;

	
	
};

