// Graphics.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <cstdlib>
#include <Windows.h>

void createSquare(COLORREF point, unsigned length, int start_x, int start_y);

int main()
{
	COLORREF White = RGB(255, 255, 255);
	createSquare(White, 500, 20, 20);
	system("pause");
	return 0;
}

void createSquare(COLORREF point, unsigned length, int start_x, int start_y)
{
	HDC hdc = GetDC(NULL);
	for (unsigned i = 0; i < length; i++)
		for (unsigned j = 0; j < length; j++)
			SetPixel(hdc,start_x + i, start_y + j, point);
	ReleaseDC(NULL, hdc);

}
