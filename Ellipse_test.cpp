#include <iostream>
#include <cstdlib>
#include <cmath>
#include <conio.h>
#define byte unsigned char
#define d(P1,P2) sqrt((P1[0] - P2[0] * P1[0] - P2[0]) + (P1[1] - P2[1]) * (P1[1] - P2[1]))

struct control {
	unsigned x;
	unsigned y;
	int* stop;

	control(unsigned x, unsigned y, int* action)
	{
		this->x = x;
		this->y = y;
		stop = action;
	}
};

void move(control* action);
void animation(int x, int y);
void printEllipse(int center[2], int x_radius, int y_radius, int start_angle, int end_angle);
int ellipse(int A1[2], int A2[2], int B1[2], int B2[2], int F1[2], int F2[2], int P[2], int i, int j, int angle);

int main(int argc, char* argv[])
{
	system("cls");
	int ch;
	control movement = control(0, 0, &ch);
	animation(0,0);
	while ((ch = _getch()) != EOF
		&& ch != 'e')
		move(&movement);

	system("cls");
	int c[2] = { 15,15 };
	printEllipse(c, 4, 3, 0, 360);
	return 0;
}

void move(control* action)
{
		system("cls");
		switch (*action->stop)
		{
		case 'w':
			if (action->y > 0)
				action->y--;
			break;
		case 'a':
			if (action->x > 0)
				action->x--;
			break;
		case 's':
			if (action->y < 16)
				action->y++;
			break;
		case 'd':
			if (action->x < 16)
				action->x++;
			break;
		default:
			break;
		}
		animation(action->x,action->y);
	return;
}

void animation(int x, int y)
{
	for (int k = 0; k < y; k++)
		printf("\n");
	for (int j = 0; j < x; j++)
		printf(" ");
	printf("O");
	return;
}

void printEllipse(int center[2], int x_radius, int y_radius, int start_angle, int end_angle)
{
	int large = x_radius > y_radius ? x_radius : y_radius;
	int small = x_radius > y_radius ? y_radius : x_radius;
	int c = sqrt(large * large - small * small);

	int F1[2] = { x_radius > y_radius ? center[0] - c : center[0], x_radius > y_radius ? center[1] : center[1] - c };
	int F2[2] = { x_radius > y_radius ? center[0] + c : center[0], x_radius > y_radius ? center[1] : center[1] + c };
	int A1[2] = { center[0] - x_radius, center[1] }, A2[2] = { center[0] + x_radius, center[1] };
	int B1[2] = { center[0], center[1] - y_radius }, B2[2] = { center[0], center[1] + y_radius };

	int P[2];

	int count = start_angle;
	byte flag = 0;
	unsigned short this_angle = 90 < end_angle ? 90 : end_angle;

	while (count < end_angle)
	{
		while (count < this_angle)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
					if (ellipse(A1, A2, B1, B2, F1, F2, P, i, j, this_angle / 90) == 2 * large)
					{
						animation(P[0],P[1]);
						flag = 1;
						break;
					}
				if (flag == 1)
					break;
			}
			count = count + 1;
		}

		switch (this_angle)
		{
		case 90:
			this_angle = 180 < end_angle ? 180 : end_angle;
			break;
		case 180:
			this_angle = 270 < end_angle ? 270 : end_angle;
			break;
		case 270:
			this_angle = end_angle;
			break;
		default:
			this_angle = end_angle;
			break;
		}
	}
}

int ellipse(int A1[2], int A2[2], int B1[2], int B2[2], int F1[2], int F2[2], int P[2], int i, int j, int angle)
{
	switch (angle)
	{
	case 0:
		P[0] = B1[0] + i;
		P[1] = B1[1] + j;
		return (int)(d(F1, P) + d(F2, P));
	case 1:
		P[0] = A2[0] - i;
		P[1] = A2[1] + j;
		return (int)(d(F1, P) + d(F2, P));
	case 2:
		P[0] = B2[0] - i;
		P[1] = B2[1] - j;
		return (int)(d(F1, P) + d(F2, P));
	case 3:
		P[0] = A1[0] + i;
		P[1] = A1[1] - j;
		return (int)(d(F1, P) + d(F2, P));
	default:
		return 0;
	}
}
