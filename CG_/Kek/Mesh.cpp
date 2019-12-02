#include "Mesh.h"



Mesh::Mesh()
{
	BoxEx();
	NGps = 0;
	TFa = 0;
}


Mesh::~Mesh()
{
}

void Mesh::SetVertices(GLfloat x, GLfloat y, GLfloat z)
{
	aux = new glm::vec3;
	aux->x = x;
	aux->y = y;
	aux->z = z;
	Verts.push_back(aux);
	
}

void Mesh::SetTexture(GLfloat x, GLfloat y, GLfloat z)
{
	aux = new glm::vec3;
	aux->x = x;
	aux->y = y;
	aux->z = z;
	Text.push_back(aux);
}

void Mesh::SetNormal(GLfloat x, GLfloat y, GLfloat z)
{
	aux = new glm::vec3;
	aux->x = x;
	aux->y = y;
	aux->z = z;
	Normais.push_back(aux);
}

void Mesh::BoxEx()
{
	
}

std::vector<glm::vec3*> Mesh::GetVerts()
{
	return Verts;
}

void Mesh::CreateGroup(std::string name)
{
	auxG = new Group;
	auxG->SetName(name);
	Gps.push_back(auxG);

	Nomes[name] = NGps;
	NGps++;


}

void Mesh::CreateFaceinGroup(std::string name, int v1, int t1, int n1, int v2, int t2, int n2, int v3, int t3, int n3)
{
	//Gps[];
	Gps[Nomes.find(name)->second]->CreateFace(v1, t1, n1, v2, t2, n2, v3, t3, n3);
	TFa++;
}

void Mesh::SetMtlinGroup(std::string name, std::string Mtl)
{
	Gps[Nomes.find(name)->second]->SetMtl(Mtl);
}

Group* Mesh::GetGroup(std::string name)
{
	return Gps[Nomes.find(name)->second];
}
