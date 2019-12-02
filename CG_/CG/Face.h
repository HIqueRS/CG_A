#pragma once
class Face
{
public:
	Face();
	~Face();
	
	void Add_Vert(int id);
	void Add_Text(int id);
	void Add_Normal(int id);

//protected:
	int Actual_Vert;
	int Actual_Text;
	int Actual_Normal;
	int Id_Vert[3];
	int Id_Text[3];
	int Id_Normal[3];
	int Max_Vert;
	int N_Vert;
};

