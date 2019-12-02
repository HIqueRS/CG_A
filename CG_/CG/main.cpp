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

int main() {
	GLFWwindow* window = NULL;
	const GLubyte* renderer;
	const GLubyte* version;

	ObjReader Reader;

	float scale_obj =1;
	bool scalebool5 = true;
	bool scalebool6 = true;

	

	/* geometry to use. these are 3 xyz points (9 floats total) to make a triangle
	*/

	Mesh *New_mesh;
	int nMesh = 1;

	New_mesh = new Mesh[nMesh];

	typedef struct Vertex {
		GLfloat coords[3];
	} VecXYZ;



	GLfloat* points;
	std::vector<glm::vec3*> Verts;
	Group *gp;
	

	
	/*for (int i = 0; i < nMesh; i++)
	{

	}*/
	New_mesh[0] = Reader.Read("LibertStatue.obj");
	//New_mesh[1] = Reader.Read("Cubo2.txt");//LibertStatue.obj
	//New_mesh[0] = IniciateMesh(New_mesh[0]);


	
	

	

	GLfloat colors[] = {
	  1.0f, 0.0f, 0.0f,
	  0.0f, 1.0f, 0.0f,
	  0.0f, 0.0f, 1.0f
	};
	
	
	/* these are the strings of code for the shaders
	the vertex shader positions each vertex point */
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
		"	gl_Position =proj* view * matrix * vec4 (vp, 1.0);"
		"}";
	// proj *

	/* the fragment shader colours each fragment (pixel-sized area of the
	triangle) */
	const char* fragment_shader =
		"#version 410\n"
		"in vec3 color;"
		"out vec4 frag_color;"
		"void main () {"
		"	frag_color = vec4 (1.0,0.0,1.0, 1.0);"
		"}";
	/* GL shader objects for vertex and fragment shader [components] */
	GLuint vs, fs, fs2;
	/* GL shader programme object [combined, to link] */
	GLuint shader_programme, shader_programme2;

	/* start GL context and O/S window using the GLFW helper library */
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	/* change to 3.2 if on Apple OS X */
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(
		640, 480, "CGR - GLSL - 03 - Moving Triangle", NULL, NULL
	);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	/* start GLEW extension handler */
	glewExperimental = GL_TRUE;
	glewInit();

	/* get version info */
	renderer = glGetString(GL_RENDERER); /* get renderer string */
	version = glGetString(GL_VERSION); /* version as a string */
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	/* tell GL to only draw onto a pixel if the shape is closer to the viewer */
	glEnable(GL_DEPTH_TEST); /* enable depth-testing */
	glDepthFunc(GL_LESS);/*depth-testing interprets a smaller value as "closer"*/

	/* a vertex buffer object (VBO) is created here. this stores an array of data
	on the graphics adapter's memory. in our case - the vertex points */
	

	for (int i = 0; i < nMesh; i++)
	{
		IniciateMesh(New_mesh[i]);
	}
	

	



	// é possível associar outros atributos, como normais, mapeamento e cores
	// lembre-se: um por vértice!
	GLuint colorsVBO;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	// note que agora o atributo 1 está definido
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1); // habilitado segundo atributo do vbo bound atual

		/* here we copy the shader strings into GL shaders, and compile them. we then
		create an executable shader 'program' and attach both of the compiled shaders.
		we link this, which matches the outputs of the vertex shader to the inputs of
		the fragment shader, etc. and it is then ready to use */
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
	//glUseProgram (shader_programme);
	//glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);

	glClearColor(0.6f, 0.6f, 0.8f, 1.0f);

	/* this loop clears the drawing surface, then draws the geometry described by
	the VAO onto the drawing surface. we 'poll events' to see if the window was
	closed, etc. finally, we 'swap the buffers' which displays our drawing surface
	onto the view area. we use a double-buffering system which means that we have
	a 'currently displayed' surface, and 'currently being drawn' surface. hence
	the 'swap' idea. in a single-buffering system we would see stuff being drawn
	one-after-the-other */
	float a = M_PI / 6;
	double b = M_PI/3;

	std::cout<<"cos de 90: " << cos(b) << std::endl;
	std::cout << "sin de 90: " << sin(b) << std::endl;

	glm::mat4 ModelMatrix(1.f),Proj;
	glm::mat4 view;
	





	CameraMovement(window,view);

	view = glm::lookAt(eye, center, up);

	float speed = 1.0f;
	float lastPosition = 0.0f;
	glUseProgram(shader_programme);

	glfwSetKeyCallback(window, keyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, 0.f, 3.0f));

	
	while (!glfwWindowShouldClose(window)) {

		static double previousSeconds = glfwGetTime();
		double currentSeconds = glfwGetTime();
		double elapsedSeconds = currentSeconds - previousSeconds;

		
		if (elapsedSeconds > 0) {
			previousSeconds = currentSeconds;
			if (fabs(lastPosition) > 1.0f) {
				speed = -speed;
				
			}
			//matrix[12] = elapsedSeconds * (speed*sin(b)) + lastPosition; //12 = x é o sen e o cos do angulo que eu tenho q aumentar aqui aqui cosseno
			//matrix[13] = elapsedSeconds * (speed*cos(b)) + lastPosition ; //13 = y  a matrix é uma identidade + movimentação aqui seno
			//no lugar do speed vai o seno e o cosseno
			//lastPosition = matrix[12];
			
			//matrix = glm::rotate(matrix,rotationY, glm::vec3(-1.0f, 0.0f, 0.0f));
			
			//Vec3 blep;
			//glRotated(45, blep.x, blep.y, blep.z);
			//glRotatef(45, -1.0f, 0.0f, 0.0f);
			//glm::rotate()
			//glm::mat4x4 mat;
			

			//aula 3 0.5 -0.5, 0.5  
		}

		
		//ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));
		//ModelMatrix = glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f);
		
		ObjTransform(window, ModelMatrix,scale_obj, scalebool5,scalebool6);

		

		CameraMovement(window,view);
		//view = glm::rotate(view, glm::radians(rotationX), glm::vec3(1.f, 0.f, 0.f));
		//view = glm::rotate(view, glm::radians(rotationY), glm::vec3(0.f, 1.f, 0.f));
		
		rotationX = 0;
		rotationY = 0;

		glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
		//Proj = glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f);
		Proj = glm::ortho(-1, 1, -1, 1, -1, 100);
		
		
		glUniformMatrix4fv(matrixLocation_1, 1, GL_FALSE, glm::value_ptr(Proj));

		glUniformMatrix4fv(matrixLocation_View, 1, GL_FALSE, glm::value_ptr(view));
		/* wipe the drawing surface clear */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//		glUseProgram (shader_programme);

		for (int i = 0; i < nMesh; i++) 
		{
			for (int g = 0; g < New_mesh[i].NGps; g++)
			{
				glBindVertexArray(New_mesh[i].Gps[g]->vao);
				glDrawArrays(GL_TRIANGLES, 0, New_mesh[i].Gps[g]->NFace * 3);
				//botar o transform aqui
			}
		}
		
		
		/* draw points 0-3 from the currently bound VAO with current in-use shader*/
		
		
		

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

