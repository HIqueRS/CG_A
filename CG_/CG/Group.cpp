#include "Group.h"



Group::Group()
{
	//BoxEx();
	NFace = 0;
}


Group::~Group()
{
}

void Group::CreateFace(int v1, int t1, int n1, int v2, int t2, int n2, int v3, int t3, int n3)
{
	

	Face Aux;
	Aux.Add_Vert(v1);
	Aux.Add_Vert(v2);
	Aux.Add_Vert(v3);

	Aux.Add_Text(t1);
	Aux.Add_Text(t2);
	Aux.Add_Text(t2);

	Aux.Add_Normal(n1);
	Aux.Add_Normal(n2);
	Aux.Add_Normal(n2);

	Vec_Faces.push_back(Aux);

	
	NFace++;
}

void Group::BoxEx()
{
	
	
}

void Group::SetName(std::string N)
{
	Name = N;
}

void Group::SetMtl(std::string M)
{
	Mtl = M;
}
