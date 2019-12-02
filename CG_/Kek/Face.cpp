#include "Face.h"



Face::Face()
{
	Actual_Vert = 0;
	N_Vert = 0;
	Max_Vert = 3;
	Actual_Normal = 0;
	Actual_Text = 0;
}


Face::~Face()
{
}

void Face::Add_Vert(int id)
{
	

	Id_Vert[Actual_Vert] = id;
	Actual_Vert++;
	

	
}

void Face::Add_Text(int id)
{

	Id_Text[Actual_Text] = id;
	Actual_Text++;
}

void Face::Add_Normal(int id)
{

	Id_Normal[Actual_Normal] = id;
	Actual_Normal++;
}
