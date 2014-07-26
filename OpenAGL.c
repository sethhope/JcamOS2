#include "OpenAGL.h"

Matrix4x4 *getIdentity(Matrix4x4 *matr)
{
	double tmpMat[4][4] = 
	{{1,0,0,1},
	{0,1,0,1},
	{0,0,1,1},
	{0,0,0,1}};

	for(int x = 0; x < 4; x++)
	{
		for(int y = 0; y < 4; y++)
		{
			matr->mat[x][y] = tmpMat[x][y];
		}
	}
	return matr;
}

Matrix4x4 *translateMatrix(Matrix4x4 *matr, Vec3 *trans)
{
	matr->mat[3][0] = trans->x;
	matr->mat[3][1] = trans->y;
	matr->mat[3][2] = trans->z;
	return matr;
}

Matrix4x4 *rotateMatrix(Matrix4x4 *matr, Vec3 *rot, TABLES *tab)
{
	matr->mat[0][3] = (getCos(rot->x*OpenPI/180, tab));
	matr->mat[1][3] = (getSin(rot->y*OpenPI/180, tab));
	matr->mat[2][3] = (getCos(rot->z*OpenPI/180, tab));
	return matr;
}
Point *calcPoint(Matrix4x4 *matr, Point *pnt)
{
	double tmpx;
	double tmpy;
	double tmpz;
	tmpx = (pnt->x*matr->mat[0][0]) + (pnt->y*matr->mat[1][0]) + (pnt->z*matr->mat[2][0]);
	tmpy = (pnt->x*matr->mat[0][1]) + (pnt->y*matr->mat[1][1]) + (pnt->z*matr->mat[2][1]);
	tmpz = (pnt->x*matr->mat[0][2]) + (pnt->y*matr->mat[1][2]) + (pnt->z*matr->mat[2][2]);
	pnt->x = tmpx
	pnt->y = tmpy
	pnt->z = tmpz
	return pnt;
}
Point *_calcPoint(Vec3 *trans, Vec3 *rot, Point *pnt, TABLES *tab)
{
	
	scalar cX = getCos(rot->x, tab);
	scalar cY = getCos(rot->y, tab);
	scalar cZ = getCos(rot->z, tab);
	scalar sX = getSin(rot->x, tab);
	scalar sY = getSin(rot->y, tab);
	scalar sZ = getSin(rot->z, tab);

	pnt->x = (pnt->x*(cZ*cY)) + (pnt->y*((cZ*sY*sX) - (sZ*cX))) + (pnt->z*((cZ*sY*sX)-(sZ*cX)));
	
	pnt->y = (pnt->x*(sZ*cY)) + (pnt->y*((sZ*sY*sX) - (cZ*cX))) + (pnt->z*((sZ*sY*cX)-(cZ*sX)));

	pnt->z = (-pnt->x*sX + pnt->z*(cY*sX));
	pnt->x += trans->x;
	pnt->y += trans->y;
	pnt->z += trans->z;

	return pnt;
}

Face *calcFace(Matrix4x4 *matr, Face *face
