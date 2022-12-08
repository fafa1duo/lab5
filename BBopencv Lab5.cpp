#include<iostream>
#include<easyx.h>
#include<graphics.h>
using namespace std;
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
#define XL 0
#define XR 200
#define YB 0
#define YT 100
int encode(float x, float y);
void Cohen_SutherLand(float x1, float y1, float x2, float y2);
void displayline(float x0, float y0, float x1, float y1, int color);
int main()
{
	Cohen_SutherLand(-10, -10, 200, 200);
	return 0;
}
int encode(float x, float y)
{
	int code = 0;
	if (x < XL) code = code | LEFT;
	else if (x > XR) code = code | RIGHT;
	if (y < YB) code = code | BOTTOM;
	else if (y > YT) code = code | TOP;
	return code;
}
void Cohen_SutherLand(float x1, float y1, float x2, float y2)
{
	initgraph(640, 480);
	setorigin(200, 200);
	displayline(XL, YB, XR, YB, 0xFFFFFF);
	displayline(XL, YT, XR, YT, 0xFFFFFF);
	displayline(XL, YB, XL, YT, 0xFFFFFF);
	displayline(XR, YB, XR, YT, 0xFFFFFF);
	int code1, code2, code;
	float x, y;
	code1 = encode(x1, y1);
	code2 = encode(x2, y2);
	while (code1 != 0 || code2 != 0)
	{
		if ((code1 & code2) != 0)
			return;
		code = code1;
		if (code1 == 0)
			code = code2;
		if ((LEFT & code) != 0)
		{
			x = XL;
			y = y1 + (y2 - y1) * (XL - x1) / (x2 - x1);
		}
		else if ((RIGHT & code) != 0)
		{
			x = XR;
			y = y1 + (y2 - y1) * (XR - x1) / (x2 - x1);
		}
		else if ((BOTTOM & code) != 0)
		{
			y = YB;
			x = x1 + (x2 - x1) * (YB - y1) / (y2 - y1);
		}
		else if ((TOP & code) != 0)
		{
			y = YT;
			x = x1 + (x2 - x1) * (YT - y1) / (y2 - y1);
		}
		if (code == code1)
		{
			x1 = x;
			y1 = y;
			code1 = encode(x, y);
		}
		else
		{
			x2 = x;
			y2 = y;
			code2 = encode(x, y);
		}
	}
	displayline(x1, y1, x2, y2, 0xFFFF00);
	getchar();
	getchar();
	closegraph();
}
void displayline(float x0, float y0, float x1, float y1, int color)
{
	int t;
	float dx, dy, k, y, x;
	dx = x1 - x0;
	dy = y1 - y0;
	k = dy / dx;
	if (k <= 1)
	{
		y = y0;
		for (t = x0; t <= x1; t++)
		{
			putpixel(t, int(y + 0.5), color);
			y = y + k;
		}
	}
	else
	{
		k = 1 / k;
		x = x0;
		for (t = y0; t <= y1; t++)
		{
			putpixel(int(x + 0.5), t, color);
			x = x + k;
		}
	}
}
