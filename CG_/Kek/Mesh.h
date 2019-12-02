#pragma once
#include "Group.h"
#include <vector>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/common.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>

typedef struct Vertex {
	GLfloat x,y,z;
} Vec3;

class Mesh
{
public:
	Mesh();
	~Mesh();
	void SetVertices( GLfloat x, GLfloat y, GLfloat z);
	void SetTexture( GLfloat x, GLfloat y, GLfloat z);
	void SetNormal( GLfloat x, GLfloat y, GLfloat z);
	void BoxEx();
	std::vector<glm::vec3*> GetVerts();
	void CreateGroup(std::string name);
	void CreateFaceinGroup(std::string name,int v1,int t1, int n1 ,int v2,int t2,int n2, int v3,int t3, int n3);
	void SetMtlinGroup(std::string name, std::string Mtl);
	Group* GetGroup(std::string name);


//protected:
	std::vector<glm::vec3*> Verts;
	std::vector<glm::vec3*> Text;
	std::vector<glm::vec3*> Normais;
	glm::vec3 *aux;
	Group g,*auxG;
	std::vector<Group*> Gps;

	int NGps;
	std::map<std::string, int > Nomes;
	int TFa;
	float scale;


};

