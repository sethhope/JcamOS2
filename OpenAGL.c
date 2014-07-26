#include "OpenAGL.h"

//sets matrix to:
//1 0 0 1
//0 1 0 1
//0 0 1 1
//0 0 0 1
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

//Translates matr by trans
Matrix4x4 *translateMatrix(Matrix4x4 *matr, Vec3 *trans)
{
	matr->mat[3][0] = trans->x;
	matr->mat[3][1] = trans->y;
	matr->mat[3][2] = trans->z;
	return matr;
}

//rotates matr by rot using tab
Matrix4x4 *rotateMatrix(Matrix4x4 *matr, Vec3 *rot, TABLES *tab)
{
	matr->mat[0][3] = (getCos(rot->x*OpenPI/180, tab));
	matr->mat[1][3] = (getSin(rot->y*OpenPI/180, tab));
	matr->mat[2][3] = (getCos(rot->z*OpenPI/180, tab));
	return matr;
}

//calculates the 3D position of a point. 2D Screenspace happens live.
Point *calcPoint(Matrix4x4 *matr, Point *pnt)
{
	double tmpx;
	double tmpy;
	double tmpz;
	tmpx = (pnt->x*matr->mat[0][0]) + (pnt->y*matr->mat[1][0]) + (pnt->z*matr->mat[2][0]);
	tmpy = (pnt->x*matr->mat[0][1]) + (pnt->y*matr->mat[1][1]) + (pnt->z*matr->mat[2][1]);
	tmpz = (pnt->x*matr->mat[0][2]) + (pnt->y*matr->mat[1][2]) + (pnt->z*matr->mat[2][2]);
	pnt->x = tmpx;
	pnt->y = tmpy;
	pnt->z = tmpz;
	return pnt;
}

//calculates all the points in a face
Face *calcFace(Matrix4x4 *matr, Face *face)
{
	
}

//2D screenspace calculations for X
int projectedx(int x, int z, int fov){
	int pro_x;
	pro_x =  (x * fov / (fov + z) + (84 / 2));
	return pro_x;
}

//2D screenspace calculations for Y
int projectedy(int y, int z, int fov){
	int pro_y;
	pro_y = 48 - (y * fov / (fov + z) + (48 / 2));
	return pro_y;

}
