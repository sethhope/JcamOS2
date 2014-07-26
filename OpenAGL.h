#ifndef _AGL_
#define _AGL_
#include "JOS2Defines.h"

#define OpenPI  3.14159265358979323846 //Incase PI isn't defined, we use our own.

typedef double scalar; //declare a standard scalar as our own variable type

typedef struct
{
	scalar x, y, z;
} Point; //create a point type with XYZ metadata

typedef struct
{
	union
	{
		struct {scalar x, y, z;};
		struct {scalar v[3];};
	};
} Vec3; //Create Vec3. Can be read as v[x] v[y] v[z] or v.x, v.y, v.z

typedef struct
{
		scalar mat[4][4];
} Matrix4x4; //Create a 4x4 matrix for our translation and rotation

typedef struct
{
	Point *p[3];
	Vec3 *pos;
	Vec3 *rot;
} Face; //create a face type so we can calculate face rotation.

//Function prototypes
Matrix4x4 *getIdentity(Matrix4x4 *matr);
Matrix4x4 *translateMatrix(Matrix4x4 *matr, Vec3 *trans);
Matrix4x4 *rotateMatrix(Matrix4x4 *matr, Vec3 *rot, TABLES *tab);
Point *calcPoint(Matrix4x4 *matr, Point *pnt);
Face *calcFace(Matrix4x4 *matr, Face *face);
int projectedx(int x, int z, int fov);
int projectedy(int y, int z, int fov);
#endif
