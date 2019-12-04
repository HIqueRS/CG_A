#include "Curva.h"


Curva::Curva()
{

}

Curva::~Curva()
{

}

vector<GLfloat> Curva::GerarCurva()
{
	int cont =0;
	vector<GLfloat> curve;
	GLfloat x, y,x0,y0;
	GLfloat* BLEPX;
	BLEPX = new GLfloat[Control_Points_X.size()];
	BLEPX = Control_Points_X.data();

	GLfloat* BLEPY;
	BLEPY = new GLfloat[Control_Points_Y.size()];
	BLEPY = Control_Points_Y.data();

	if (Control_Points_X.size() > 4)
	{
		cont = 3;
	}

	int i0, i1, i2, i3;
	
	for (int i = 0; i < Control_Points_X.size()- cont; i++)
	{		
		for (float t = 0; t <= 1; t += inc) 
		{
			x = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * BLEPX[i] +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * BLEPX[i + 1] +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * BLEPX[i + 2] +
				(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * BLEPX[i + 3]) / 6);
			y = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * BLEPY[i] +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * BLEPY[i + 1] +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * BLEPY[i + 2] +
				(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * BLEPY[i + 3]) / 6);

			
			curve.push_back(x);
			curve.push_back(y);

			x0 = x;
			y0 = y;

			i0 = i;
			i1 = i + 1;
			i2 = i + 2;
			i3 = i + 3;
		}
	}

	cout << i0;
	
	for (float t = 0; t <= 1; t += inc)
	{
		x = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * BLEPX[i1] +
			(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * BLEPX[i2] +
			(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * BLEPX[i3] +
			(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * x0) / 6);
		y = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * BLEPY[i1] +
			(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * BLEPY[i2] +
			(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * BLEPY[i3] +
			(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * y0) / 6);


		curve.push_back(x);
		curve.push_back(y);
	}
	
	

	return curve;
}

vector<GLfloat> Curva::GerarCurvaInterna(vector<GLfloat> Cur,bool q)
{
	vector<GLfloat> curve;
	GLfloat* BLEPX;
	BLEPX = new GLfloat[curve.size()];
	BLEPX = curve.data();

	for (int i = 0; i < Cur.size()-2 ; i+=2)//
	{
		double w, h,x1,x2,y1,y2,teta,alfa;
		
		glm::vec2 ab,ad;

		
		
		x1 = Cur[i];
		y1 = Cur[i + 1];
		if (i + 2 > Cur.size()-2)
		{
			x2 = Cur[0];
			y2 = Cur[0];
		}
		else
		{
			x2 = Cur[i + 2];
			y2 = Cur[i + 3];
		}
		
		
		w = x2 - x1;
		h = y2 - y1;	
		ab.x = x2 - x1;
		ab.y = y2 - y1;
		ad.x = x2 - x1;
		ad.y = 0;

		
		glm::normalize(ab);
		glm::normalize(ad);

		/*w = glm::normalize(w);
		h = glm::normalize(h);*/

		teta = atan(h / w) ;

		//cout << teta * 180 / PI;

		//teta = glm::normalize(teta);
		//teta = glm::acos(glm::dot(ab,ad));		

		if ((w > 0))
		{
			if (q)
			{
				alfa = teta + PI / 2;
			}
			else
			{
				alfa = teta - PI / 2;
			}
			
			
		}
		else
		{
			if (!q)
			{
				alfa = teta + PI / 2;
			}
			else
			{
				alfa = teta - PI / 2;
			}
		}
		
		curve.push_back(cos(alfa ) * 20 + x1);		
		curve.push_back(sin(alfa ) * 20 + y1);

		
		
	}
	return curve;
}

vector<GLfloat> Curva::GerarCurvaExterna(vector<GLfloat> Cur)
{
	return vector<GLfloat>();
}

void Curva::CreateObj()
{
	ArqObj.open("../CG/pista.obj");
	ArqObj.clear();
	ArqObj << "#teste" << endl;
	ArqObj << "mtllib Grass_Block.mtl" << endl;
	for (int i = 0; i < CurvaE.size() ; i+=2)
	{
		ArqObj << "v " << CurvaI[i] << " " << "1.0" << " " << CurvaI[i+1] << endl;
	}
	for (int i = 0; i < CurvaE.size() ; i+=2)
	{
		ArqObj << "v " << CurvaE[i] << " " << "1.0" << " " << CurvaE[i+1] << endl;
	}
	ArqObj << "g group" << endl;
	ArqObj << "usemtl Grass_Block_TEX" << endl;

	for (int i = 1; i < CurvaE.size()/2 ; i++)
	{
		ArqObj << "f " << i  << "/1/1 " << i + 1 << "/1/1 " << CurvaE.size()/2 + i  <<"/1/1" << endl;
		ArqObj << "f " << CurvaE.size()/2 + i  << "/1/1 " << CurvaE.size()/2 + i + 1  <<"/1/1 "<<i + 1  <<"/1/1"<< endl;
	}

		ArqObj << "f " << CurvaE.size() / 2 << "/1/1 " << 1 << "/1/1 " << CurvaE.size() <<"/1/1" << endl;
		ArqObj << "f " << CurvaE.size()   << "/1/1 " << CurvaE.size()/2 +  1  <<"/1/1 "<< 1  <<"/1/1"<< endl;


	ArqObj.close();
}
