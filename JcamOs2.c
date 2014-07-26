#include "JOS2Defines.h"
#include "OpenAGL.h"
bool key[4];
TABLES *tab;
int projectedx(int x, int z, int fov){
	int pro_x;
	pro_x =  (x * fov / (fov + z) + (84 / 2));
	return pro_x;
}

int projectedy(int y, int z, int fov){
	int pro_y;
	pro_y = 48 - (y * fov / (fov + z) + (48 / 2));
	return pro_y;

}
void drawline3(int x, int y, int z, int x1, int y1, int z1){
	x = projectedx(x, z, FOV);
	y = projectedy(y, z, FOV);
	x1 = projectedx(x1, z1, FOV);
	y1 = projectedy(y1, z1, FOV);
	if(x >= 0 && x1 >= 0 && y >= 0 && y1 >= 0 && x <= 84 && y <= 48 && x1 <= 84 && y1 <= 48){
	LcdLine( x, x1, y, y1, PIXEL_ON);
	}
}

void init()
{
	DDRC &= 0x3E;
	LcdInit();
	LcdContrast(0x7F);
    LcdContrast(0x40);
	LcdClear();
	LcdGotoXYFont(1,1);
	LcdFStr(FONT_1X,(unsigned char*)PSTR("Generating Tables"));
	LcdUpdate();
	tab = malloc(sizeof(*tab));
	tab = genTables(tab);
	LcdClear();
}
int main()
{
	init();
	LcdGotoXYFont(1,1);
	LcdFStr(FONT_1X,(unsigned char*)PSTR("Allocating Memory"));
	LcdUpdate();
	Matrix4x4 *mat = malloc(sizeof(*mat));
	Vec3 *trans = malloc(sizeof(*trans));
	Vec3 *rot = malloc(sizeof(*rot));
	LcdClear();
	LcdGotoXYFont(1, 1);
	LcdFStr(FONT_1X,(unsigned char*)PSTR("Done"));
	LcdUpdate();
	double x[4] = {1, 1, 1, 20};
	double y[4] = {1, 1, 20, 1};
	double z[4] = {1, 20, 1, 1};
	int t = z[0];
	unsigned char tC[4];
	trans->x = 0;
	trans->y = 0;
	trans->z = 20;
	mat = getIdentity(mat);
	mat = translateMatrix(mat, trans);
	for(int i = 0; i < 4; i++)
	{
		Point *p = malloc(sizeof(*p));
		p->x = x[i];
		p->y = y[i];
		p->z = z[i];
		p = calcPoint(mat, p);
		x[i] = p->x;
		y[i] = p->y;
		z[i] = p->z;
		free(p);
	}
	int up = 1;
	int dn = 1;
	int lt = 1;
	int bt = 1;
	int rt = 1;
	double tX = 0;
	double tY = 0;
	double tZ = 0;
	double rX = 0;
	double rY = 0;
	double rZ = 0;
	while(1)
	{
		up = (PINC & 0x20);
		dn = (PINC & 0x04);
		rt = (PINC & 0x10);
		bt = (PINC & 0x08);
		lt = (PINC & 0x02);
		mat = getIdentity(mat);
		
		/*if(up == 0 && bt != 0)
		{
			tY += 1;
		}
		if(up == 0 && bt == 0)
		{
			tZ += 1;
		}
		if(dn == 0 && bt != 0)
		{
			tY -= 1;
		}
		if(dn == 0 && bt == 0)
		{
			tZ -= 1;
		}
		if(lt == 0)
		{
			tX += 1;
		}
		if(rt == 0)
		{
			tX -= 1;
		}*/

		rX++;
		if(rX >= 360)
		{
			rX = 0;
		}
		rY++;
		if(rY >= 360)
		{
			rY = 0;
		}
		rZ++;
		if(rZ >= 360)
		{
			rZ = 0;
		}
		trans->x = tX;
		trans->y = tY;
		trans->z = tZ;
		rot->x = rX;
		rot->y = rY;
		rot->z = rZ;
		mat = rotateMatrix(mat, rot, tab);
		mat = translateMatrix(mat, trans);
		for(int i = 0; i < 4; i++)
		{
			Point *p = malloc(sizeof(*p));
			p->x = x[i];
			p->y = y[i];
			p->z = z[i];
			p = calcPoint(mat, p);
			x[i] = p->x;
			y[i] = p->y;
			z[i] = p->z;
			free(p);
		}
		t = rX;
		itoa(t, (char*)tC, 10);
		LcdClear();

		
		LcdGotoXYFont(1, 1);
		LcdStr(FONT_1X,tC);
		drawline3(x[0], y[0], z[0], x[1], y[1], z[1]);
		drawline3(x[0], y[0], z[0], x[2], y[2], z[2]);
		drawline3(x[0], y[0], z[0], x[3], y[3], z[3]);
		LcdUpdate();

	}

}
