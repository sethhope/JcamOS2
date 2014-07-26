#ifndef _AGL_
#define _AGL_
#include "JOS2Defines.h"

#define OpenPI  3.14159265358979323846

typedef double scalar;
typedef struct
{
	scalar x, y, z;
} Point;
typedef struct
{
	Point *p[3];
	scalar x, y, z, rx, ry, rz;
} Face;
typedef struct
{
	union
	{
		struct {scalar x, y, z;};
		struct {scalar v[3];};
	};
} Vec3;
typedef struct
{
		scalar mat[4][4];
} Matrix4x4;


Matrix4x4 *getIdentity(Matrix4x4 *matr);
Matrix4x4 *translateMatrix(Matrix4x4 *matr, Vec3 *trans);
Matrix4x4 *rotateMatrix(Matrix4x4 *matr, Vec3 *rot, TABLES *tab);
Point *calcPoint(Matrix4x4 *matr, Point *pnt);
Point *_calcPoint(Vec3 *trans, Vec3 *rot, Point *pnt, TABLES *tab);
Face *calcFace(Matrix4x4 *matr, Face *face);

#endif
