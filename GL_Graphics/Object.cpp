#include "Object.h"

Object::Object()
{}

Object::Object(int SI, int SF, unsigned int* SAI, GLfloat* SAF)
	:
	size_indexs(SI), size_Figure(SF)
{
	figure = new GLfloat[SF];
	indexs = new unsigned int[SI];
	for (int i = 0; i < SF; i++)
	{
		figure[i] = SAF[i] ;
	}
	for (int i = 0; i < SI; i++)
	{
		indexs[i] = SAI[i];
	}
}

Object::~Object()
{
	delete[] figure;
	delete[] indexs;
}