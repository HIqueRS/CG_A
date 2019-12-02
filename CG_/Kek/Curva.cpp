#include "Curva.h"


Curva::Curva()
{

}

Curva::~Curva()
{

}

vector<GLfloat> Curva::GerarCurva()
{

	vector<GLfloat> curve;
	GLfloat x, y;

	for (int i = 0; i < Control_Points_X.size()/4; i++)
	{
		for (float t = 0; t <= 1; t += inc) {
			x = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * Control_Points_X[i] +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * Control_Points_X[i + 1] +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * Control_Points_X[i + 2] +
				(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * Control_Points_X[i + 3]) / 6);
			y = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * Control_Points_Y[i] +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * Control_Points_Y[i + 1] +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * Control_Points_Y[i + 2] +
				(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * Control_Points_Y[i + 3]) / 6);

			curve.push_back(x);
			curve.push_back(y);
		}
	}
	
	

	return curve;
}

vector<GLfloat> Curva::GerarCurvaInterna()
{
	return vector<GLfloat>();
}

vector<GLfloat> Curva::GerarCurvaExterna()
{
	return vector<GLfloat>();
}
