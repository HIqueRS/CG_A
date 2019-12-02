#pragma once
#include "Mesh.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class ObjReader
{
public:
	ObjReader();
	~ObjReader();
	Mesh Read(std::string name);

	string line;
	string nameg;

	int v1=1, v2=1, v3=1;
	int t1=1, t2=1, t3=1;
	int n1=1, n2=1, n3=1;
	int v4=1, t4=1, n4=1;

	float maiorx = 0, menorx = 99999999999, maiory = 0, menory = 99999999999, maiorz = 0, menorz = 99999999999;

	float scale;
};

