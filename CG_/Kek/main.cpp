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

#include "ObjReader.h"

#include "Mesh.h"

#include "Curva.h"

#define M_PI   3.14159265358979323846264338327950288

#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

GLfloat  Cam_rotx = 0.0f;
GLfloat Cam_PosZ = 3.0f;

glm::vec3  center = glm::vec3(0.0f, 0.0f, 0.0f) , up = glm::vec3(0.0f, 1.0f, 0.0f) , camF = glm::vec3(0.0f, 0.0f, -1.0f);
float camX = sin(glfwGetTime()) * 10;
float camZ = cos(glfwGetTime()) * 10;

glm::vec3 eye = glm::vec3(camX, 0.0, camZ);

using namespace std;

Curva curva;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	//std::cout << key << std::endl;

	const GLfloat rotationSpeed = 10;
	

	// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_UP:
			rotationX -= rotationSpeed;
			
			break;
		case GLFW_KEY_DOWN:
			rotationX += rotationSpeed;
			break;
		case GLFW_KEY_RIGHT:
			rotationY -= rotationSpeed;
			break;
		case GLFW_KEY_LEFT:
			rotationY += rotationSpeed;
			break;
		case GLFW_KEY_O:
			curva.CreateObj();
			break;
		}


	}
}

void CameraMovement(GLFWwindow * window, glm::mat4 &view)
{
	float radius = 10.0f;	
	

	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_0)) {

		//Cam_PosZ -= 0.01;
		eye += 0.01f * camF;
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_9)) {


		//Cam_PosZ += 0.01;
		eye -= 0.01f * camF;

	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_LEFT)) {

		//Cam_rotx -= 0.01f;
		//
		//camX = sin(eye.x + Cam_rotx)*radius ;
		//camZ = cos(eye.z + Cam_rotx) *radius ;

		//
		//eye = glm::vec3(camX, eye.y, camZ);
		////Cam_rotx -= 0.01;
		//eye -= glm::normalize(glm::cross(camF, up)) * 0.01f;
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_RIGHT)) {

		/*Cam_rotx += 0.01;

		camX = sin(Cam_rotx)*radius;
		camZ = cos(Cam_rotx) *radius;*/
		//Cam_rotx += 0.01;
		//eye += glm::normalize(glm::cross(camF, up)) * 0.01f;
	}

	
	view = glm::lookAt(eye, center, up);


	/*float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));*/

	
}

void ObjTransform(GLFWwindow * window, glm::mat4 &ModelMatrix,float &scale,bool &scalebool5,bool &scalebool6)
{
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotationX), glm::vec3(1.f, 0.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotationY), glm::vec3(0.f, 1.f, 0.f));

	

	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W)) 
	{
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, 0.f, -0.01f));
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S))
	{
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, 0.f, +0.01f));
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D))
	{
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.01f, 0.f, 0.0f));
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A))
	{
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-0.01f, 0.f, 0.0f));
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_Q))
	{
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, 0.01f, 0.0f));
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_E))
	{
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, -0.01f, 0.0f));
	}

	
	if (scalebool5)
	{
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_5))
		{
			//scale += 0.01;
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.9F, 0.9F, 0.9F));
			scalebool5 = false;
		}
	}
	
	if (GLFW_RELEASE == glfwGetKey(window, GLFW_KEY_5))
	{
		scalebool5 = true;
	}

	if (scalebool6)
	{
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_6))
		{
			//scale += 0.01;
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.1F, 1.1F, 1.1F));
			scalebool6 = false;
		}
	}

	if (GLFW_RELEASE == glfwGetKey(window, GLFW_KEY_6))
	{
		scalebool6 = true;
	}

}

void IniciateMesh(Mesh &m) {
	
	int ngroup;

	ngroup = m.NGps;

	for (int i = 0; i < ngroup; i++)
	{
		int nfaces;
		nfaces = m.Gps[i]->NFace;
		GLfloat* points;
		points = new GLfloat[nfaces*9];

		std::vector<glm::vec3*> Verts;
		Group *gp;

		Verts = m.GetVerts();
		gp = m.Gps[i];

		

		int c = 0;

		glGenVertexArrays(1, &m.Gps[i]->vao);
		glBindVertexArray(m.Gps[i]->vao);


		cout << "q?";
		for (int f = 0; f < nfaces; f++)
		{
			for (int v = 0; v < 3; v++)
			{
				points[c] = Verts[gp->Vec_Faces[f].Id_Vert[v] - 1]->x;
				//cout << points[c] << "e agr?\n ";
				c++;

				points[c] = Verts[gp->Vec_Faces[f].Id_Vert[v] - 1]->y;
				//cout << points[c] << "e agr?\n ";
				c++;
				points[c] = Verts[gp->Vec_Faces[f].Id_Vert[v] - 1]->z;
				//cout << points[c] << "e agr?\n ";
				c++;

			}

		}


		glGenBuffers(1, &m.Gps[i]->vboV);
		glBindBuffer(GL_ARRAY_BUFFER, m.Gps[i]->vboV);
		glBufferData(GL_ARRAY_BUFFER, m.Gps[i]->NFace * 3 * 3 * sizeof(GLfloat), points, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, m.Gps[i]->vboV);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		

	}

	
}

bool teste = false;
bool testec = false;

GLuint vao;

vector<GLfloat> Points_C;

int n_max; 

void CreateCurve() 
{
	glGenVertexArrays(1, &curva.VAO);
	glBindVertexArray(curva.VAO);

	vector<GLfloat> cur;
	cur = curva.GerarCurva();

	glGenBuffers(1, &curva.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, curva.VBO);
	glBufferData(GL_ARRAY_BUFFER, cur.size() * sizeof(GLfloat), cur.data(), GL_STATIC_DRAW);
	n_max = cur.size()/2;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	////

	glGenVertexArrays(1, &curva.VAOI);
	glBindVertexArray(curva.VAOI);

	vector<GLfloat> cur_i;
	cur_i = curva.GerarCurvaInterna(cur,true);
	curva.CurvaI = cur_i;

	glGenBuffers(1, &curva.VBOI);
	glBindBuffer(GL_ARRAY_BUFFER, curva.VBOI);
	glBufferData(GL_ARRAY_BUFFER, cur_i.size() * sizeof(GLfloat), cur_i.data(), GL_STATIC_DRAW);
	n_max = cur_i.size() / 2;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	////

	glGenVertexArrays(1, &curva.VAOE);
	glBindVertexArray(curva.VAOE);

	vector<GLfloat> cur_E;
	cur_E = curva.GerarCurvaInterna(cur,false);
	curva.CurvaE = cur_E;

	glGenBuffers(1, &curva.VBOE);
	glBindBuffer(GL_ARRAY_BUFFER, curva.VBOE);
	glBufferData(GL_ARRAY_BUFFER, cur_E.size() * sizeof(GLfloat), cur_E.data(), GL_STATIC_DRAW);
	n_max = cur_E.size() / 2;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);


	testec = true;
}


void create_point(double xpos, double ypos)
{
	

	

	Points_C.push_back(xpos);
	Points_C.push_back(ypos);

	curva.Control_Points_X.push_back(xpos);
	curva.Control_Points_Y.push_back(ypos);


	
	

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, Points_C.size() * sizeof(GLfloat), Points_C.data(), GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2, GL_FLOAT, GL_FALSE, 0, NULL);

	

	if (Points_C.size() >= 8)
	{

		CreateCurve();



		//cout << Points_C[4];
	}
	
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		cout << " x: " << xpos << " y: " << ypos << "\n";		
		
		ypos *= -1;
		ypos += 600;
		
		create_point(xpos, ypos);
		
		//add point to curve

		teste = true;
	}
		
}



int main() {
	GLFWwindow* window = NULL;
	const GLubyte* renderer;
	const GLubyte* version;

	
	

	GLfloat colors[] = {
	  1.0f, 0.0f, 0.0f,
	  0.0f, 1.0f, 0.0f,
	  0.0f, 0.0f, 1.0f
	};
	
	
	
	const char* vertex_shader =
		"#version 410\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vc;"
		"uniform mat4 matrix;"
		"uniform mat4 proj;"
		"uniform mat4 view;"
		"out vec3 color;"
		"void main () {"
		"   color = vc;"
		"	gl_Position = proj * matrix * vec4 (vp, 1.0);"
		"}";
	//gl_Position = proj * view * matrix * vec4 (vp, 1.0);

	
	const char* fragment_shader =
		"#version 410\n"
		"in vec3 color;"
		"out vec4 frag_color;"
		"void main () {"
		"	frag_color = vec4 (1.0,0.0,0, 1.0);"
		"}";
	
	GLuint vs, fs;
	
	GLuint shader_programme;

	
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	

	window = glfwCreateWindow(
		800, 600, "CGR - GLSL - 03 - Moving Triangle", NULL, NULL
	);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	
	glewExperimental = GL_TRUE;
	glewInit();

	
	renderer = glGetString(GL_RENDERER); 
	version = glGetString(GL_VERSION); 
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LESS);

	GLfloat points[] = { 0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f };

	GLuint points_vbo;
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), points, GL_STATIC_DRAW);

	GLuint vao1;
	glGenVertexArrays(1, &vao1);
	glBindVertexArray(vao1);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	
	GLuint colorsVBO;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1); 

		
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	int matrixLocation = glGetUniformLocation(shader_programme, "matrix");
	int matrixLocation_1 = glGetUniformLocation(shader_programme, "proj");
	int matrixLocation_View = glGetUniformLocation(shader_programme, "view");
	

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	
	
	glm::mat4 ModelMatrix(1.f),Proj(1.f);
	glm::mat4 view;
	





	//CameraMovement(window,view);

	//view = glm::lookAt(eye, center, up);//hmmmm


	glUseProgram(shader_programme);

	glfwSetKeyCallback(window, keyCallback);
	
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	
	Proj = ModelMatrix;
	//Proj = glm::ortho(-1, 1,1,-1,-1,1);
	Proj = glm::ortho(0.0f, 800.0f,0.0f,600.0f,-1.0f,1.0f);
	
	
	

	//ModelMatrix = glm::scale(ModelMatrix, glm::vec3(502.0F, 502.1F, 1.1F));
	
	while (!glfwWindowShouldClose(window)) {

		static double previousSeconds = glfwGetTime();
		double currentSeconds = glfwGetTime();
		double elapsedSeconds = currentSeconds - previousSeconds;		

		//CameraMovement(window,view);		
		
		glUniformMatrix4fv(matrixLocation_1, 1, GL_FALSE, glm::value_ptr(Proj));

		glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
		//Proj = glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f);
		
		

		glUniformMatrix4fv(matrixLocation_View, 1, GL_FALSE, glm::value_ptr(view));
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glBindVertexArray(vao1);
		glDrawArrays(GL_LINE_LOOP, 0, 3);
		
		if (teste)
		{		
			
			glBindVertexArray(vao);
			glPointSize(5);
			glDrawArrays(GL_POINTS, 0, Points_C.size()/2);
			
		}
		
		
		if (testec)
		{
			glBindVertexArray(curva.VAO);
			glPointSize(3);
			glDrawArrays(GL_LINE_LOOP, 0, n_max);

			glBindVertexArray(curva.VAOI);
			glPointSize(3);
			glDrawArrays(GL_LINE_LOOP, 0, n_max);

			glBindVertexArray(curva.VAOE);
			glPointSize(3);
			glDrawArrays(GL_LINE_LOOP, 0, n_max);
		}
		
		

		/* update other events like input handling */
		glfwPollEvents();
		/* put the stuff we've been drawing onto the display */
		glfwSwapBuffers(window);
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, 1);
		}
	}

	/* close GL context and any other GLFW resources */
	glfwTerminate();
	return 0;
}

